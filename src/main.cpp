#include <csignal>
#include <iostream>
#include <format>
#include <regex>

#include <tgbot/tgbot.h>

#include "API/ScheduleAPI.h"
#include "Types/ScheduleDay.h"

void addBotCommands(TgBot::Bot &bot, ScheduleAPI &API);
std::vector<std::string> parseArguments(const std::string &text);

// First argument - bot token
// Second argument - API token
// Third argument - webhook URL
int main(int argc, char *argv[]) {
    if(argc < 2){
        std::cout << "Missing bot token argument! Aborting." << std::endl;
        return 1;
    }
    if(argc < 3){
        std::cout << "Missing API token argument! Some functions won't work." << std::endl;
    }

    ScheduleAPI API((argc >= 3) ? argv[2] : "");

    TgBot::CurlHttpClient curlHttpClient;
    TgBot::Bot bot(argv[1], curlHttpClient);

    addBotCommands(bot, API);

    std::signal(SIGINT, [](int s) {
        std::cout << "Received SIGINT" << std::endl;
        exit(0);
    });



    try {
        bot.getApi().deleteWebhook();

        if(argc < 4){
            TgBot::TgLongPoll longPoll(bot);
            //Move inside the loop if you want to see each beginTime it restarts
            std::cout << "Long poll started" << std::endl;
            while (true) {
                longPoll.start();
            }
        } else{
            TgBot::TgWebhookTcpServer webhookServer(8080, bot);
            std::cout << "Server starting" << std::endl;
            bot.getApi().setWebhook(argv[4]);
            webhookServer.start();
        }
    } catch (std::exception& e) {
        std::cout << "error: " << e.what() << std::endl;
    }

    return 0;
}

void addBotCommands(TgBot::Bot &bot, ScheduleAPI &API){
    bot.getEvents().onCommand("start", [&bot](const TgBot::Message::Ptr& message) {
        bot.getApi().sendMessage(message->chat->id, "Hi!");
    });
    bot.getEvents().onCommand("te", [&bot, &API](const TgBot::Message::Ptr& message) {
        std::vector<std::string> args = parseArguments(message->text);
        auto timeNow = std::chrono::system_clock::now();

        uint16_t yearToCheck = std::stoul(std::format("{:%Y}", timeNow));
        uint8_t monthToCheck;
        uint8_t dayToCheck;

        if(args.empty()){
            monthToCheck = std::stoul(std::format("{:%m}", timeNow));
            dayToCheck = std::stoul(std::format("{:%d}", timeNow));
        } else{
            std::regex parse(R"(^(\d{1,2})\.(\d{1,2})$)");
            std::smatch matches;
            if(!std::regex_search(args[0], matches, parse)){
                bot.getApi().sendMessage(message->chat->id, "Не вірні аргументи!", true, message->messageId);
                return;
            }
            monthToCheck = std::stoul(matches[2]);
            dayToCheck = std::stoul(matches[1]);
        }

        try{
            ScheduleDay test = API.getDay(
                    "se-124b",
                    yearToCheck,
                    monthToCheck,
                    dayToCheck
                    );
            bot.getApi().sendMessage(message->chat->id, test.getTelegramMessage(), true, message->messageId, nullptr, "HTML");
        } catch(const std::runtime_error &e){
            bot.getApi().sendMessage(message->chat->id, "Ви зробили крінж!", true, message->messageId);
        }
    });
}

std::vector<std::string> parseArguments(const std::string &text){
    std::vector<std::string> args;

    std::regex parse("\\s+(\\S+)");
    std::smatch matches;
    std::string::const_iterator searchStart(text.cbegin());
    while (std::regex_search(searchStart, text.cend(), matches, parse)) {
        args.emplace_back(matches[1]);
        searchStart = matches.suffix().first;
    }

    return args;
}
