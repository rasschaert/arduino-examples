// photocell + 10k pulldown resistor analog input pin
const int photocellPin = A0;
// analog reading of photocell
int photocellReading;

// whether we consider it to be night or not
bool isNight;

// when we first started recording night
int initialNightBoundaryPassTime;
// when we last recorded night
int lastNightBoundaryPassTime;
// how many times we've recorded night successively
int nightBoundaryPassCount;

// reading (0-1023) below which we consider it to be night
const int nightBoundary = 200;
// how long  we should have passed the boundary in order for it to actually count
const int nightBoundaryPassTimeBoundary = 5000;

void setup()
{
    Serial.begin(9600);
}

void updateNightState()
{
    photocellReading = analogRead(photocellPin);

    if (photocellReading <= nightBoundary) {
        if (nightBoundaryPassCount == 0) {
            initialNightBoundaryPassTime = millis();
        }

        lastNightBoundaryPassTime = millis();
        nightBoundaryPassCount++;
    } else {
        nightBoundaryPassCount = 0;
    }

    if (nightBoundaryPassCount == 0) {
        if (millis() >= (lastNightBoundaryPassTime +
            nightBoundaryPassTimeBoundary)) {
            isNight = false;
        }
    } else {
        if (millis() >= (initialNightBoundaryPassTime +
            nightBoundaryPassTimeBoundary)) {
            isNight = true;
        }
    }
}

void loop()
{
    updateNightState();

    Serial.print("State: ");
    Serial.println(isNight ? "NIGHT" : "DAY");
    Serial.print("Photocell reading: ");
    Serial.println(photocellReading);

    delay(500);
}
