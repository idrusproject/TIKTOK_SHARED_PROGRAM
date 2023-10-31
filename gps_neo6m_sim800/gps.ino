void gpsInfo()
{
  if (gps.location.isValid())
  {
    gpsValid = true;
    float latitude = gps.location.lat();
    float longitude = gps.location.lng();
    float altitude = gps.altitude.meters();

    // Print latitude and longitude to Serial Monitor
    Serial.print("Latitude: ");
    Serial.println(latitude, 6);
    Serial.print("Longitude: ");
    Serial.println(longitude, 6);
    Serial.print("Altitude: ");
    Serial.println(altitude);

    // Create Google Maps URL format
    //        googleMapsURL = "https://www.google.com/maps/search/?api=1&query=";
    googleMapsURL = String(gps.location.lat(), 6);
    googleMapsURL += ",";
    googleMapsURL += String(gps.location.lng(), 6);

    Serial.print("Google Maps URL: ");
    Serial.println(googleMapsURL);

    digitalWrite(led, 1);
  }
  else
  {
    Serial.println("Location: Not Available");
    digitalWrite(led, 1);
    delay(10);
    digitalWrite(led, 0);
    delay(10);
  }


  Serial.print("Date: ");
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.println(gps.date.year());
    digitalWrite(led, 1);
  }
  else
  {
    Serial.println("Not Available");
    digitalWrite(led, 1);
    delay(10);
    digitalWrite(led, 0);
    delay(10);
  }


  Serial.print("Time: ");
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.println(gps.time.centisecond());
    digitalWrite(led, 1);
  }
  else
  {
    Serial.println("Not Available");
    digitalWrite(led, 1);
    delay(10);
    digitalWrite(led, 0);
    delay(10);
  }

  Serial.println();
  Serial.println();
  delay(100);
}
