void handleNewMessages(int numNewMessages)
{
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") {
      from_name = "Guest";
    }

    if (text == "/start") {
      String welcome = "Hi, " + from_name + ".\n";
      welcome += "Sistem sudah online :) \n";

      bot.sendMessage(chat_id, welcome);
    }
    
    if (text.equals("/cek_suhu")) { // Corrected the closing parenthesis
      String welcome = "Suhu saat ini : ";
      welcome += String(t);
      welcome += "°C";
      bot.sendMessage(chat_id, welcome);
    }
  }
}
