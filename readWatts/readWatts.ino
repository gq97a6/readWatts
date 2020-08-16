#define PROB_FREQ 60 //Frequency of measurements
#define MAX_WAT 4900 //Maximal power consumption (x+200)
#define IMP_PER_KWH 2500 //Blinks per kwh
#define THRESHOLD_VAL 2000 //Threshold value of brightnes
#define INPUT_PIN 4

long probeFreq;
float blinkWat;
int delayFreq;

void setup()
{
  Serial.begin(115200);

  probeFreq = 1000 /PROB_FREQ;
  blinkWat = 1000 /IMP_PER_KWH;
  delayFreq = 3600000 / MAX_WAT * blinkWat;
}

long sum;
long num;
int val;

long probeAlarm;
long lastBlink;
float diff;
float wats;

void loop()
{
  //Collect data
  num++;
  sum += analogRead(INPUT_PIN);
  
  if(probeAlarm <= millis())
  {
    //Calculate average
    val = sum / num;
    sum = num = 0;

    //If value is higher than threshold
    if(val >= THRESHOLD_VAL)
    {
      //Wait after blink for at least shortest possible delay according to MAX_WAT
      probeAlarm = millis() + delayFreq;

      //Calculate watts consumption
      diff = millis() - lastBlink;
      wats = 1000 / diff * 3600 * blinkWat;

      //Save timestamp
      lastBlink = millis();
      
      Serial.println(wats);
    }
    else
    {
      //Wait to next measurement
      probeAlarm = millis() + probeFreq;
    }
  }
}
