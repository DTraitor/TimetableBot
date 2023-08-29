# Schedule Telegram Bot

Telegram bot based on [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) library. Receives schedule through NAU Schedule API.

# Dependencies

Dependencies (listed in vcpkg.json):
* cpr
* rapidjson
* curl (technically optional but requires some changes in the main function to run)
* tgbot-cpp

# Running

The bot supports multiple launch arguments:
1. Telegram Bot Token (required)
2. Schedule API Token (optional)
3. Telegram Webhook URL (optional)

# License

[The MIT License](https://github.com/DTraitor/ChessGame/blob/master/LICENSE).
