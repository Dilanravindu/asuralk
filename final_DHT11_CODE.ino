
// Include the libraries:
#include <DHT.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  //0x3F is the i2c address, while 16 = columns, and 2 = rows. 

#define DHTPIN 8 // digital pin connected to sensor

// Set DHT type, uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino:

void setup(){
  Serial.begin(9600); // Begin serial communication at a baud rate of 9600:
  lcd.init();                      // initialize the lcd 
  lcd.init();
  dht.begin();        //Initialize the DHT11 sensor
  lcd.backlight();    //Activate backlight 
}

void loop()
{
  // Reading temperature or humidity takes about 250 milliseconds!
  float t = dht.readTemperature();// Read the temperature as Celsius:
  float h = dht.readHumidity(); // Read the humidity in %:
  
  if (isnan(h) || isnan(t)) { // Check if any reads failed and exit early (to try again):
    Serial.println("Failed to read from DHT sensor!");
  } 
  
  lcd.setCursor(0,0); // set the cursor on the first row and column
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223);// is the code for the degree symbol,
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  delay(1000); // Delay 1 second, as the DHT11 sampling rate is 1Hz
}
