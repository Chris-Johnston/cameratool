
// analog input pin with photoresistor
#define IN_PIN A0

// sampling rate is apparently 150khz for the mega 2560 board, which is overkill for this purpose
#define SAMPLING_RATE_MICROSECONDS 500

// how many seconds of sampling buffer to use
#define SAMPLES_SECONDS 1

// the number of samples
#define SAMPLES_COUNT (SAMPLES_SECONDS * 1000 * (1000 / SAMPLING_RATE_MICROSECONDS))

int sample_index = 0;
int samples[SAMPLES_COUNT] = {0};

void setup() {
    Serial.begin(115200);
    pinMode(IN_PIN, INPUT);

    pinMode(LED_BUILTIN, OUTPUT);

    
    digitalWrite(LED_BUILTIN, 0);
    delay(500);
    digitalWrite(LED_BUILTIN, 1);
    delay(500);

    digitalWrite(LED_BUILTIN, 0);
    delay(500);
    digitalWrite(LED_BUILTIN, 1);
    delay(500);

    digitalWrite(LED_BUILTIN, 0);
}

void dump() {
    int smin = samples[0], smax = samples[0];

    digitalWrite(LED_BUILTIN, 0);
    for (int sample = 0; sample < SAMPLES_COUNT; sample++) {
        int actual_sample = (sample_index + sample) % SAMPLES_COUNT;

        // digitalWrite(LED_BUILTIN, sample % 2);

        Serial.print(sample);
        Serial.print(",");
        Serial.print(samples[actual_sample]);
        Serial.print("\n");

        smin = min(samples[actual_sample], smin);
        smax = max(samples[actual_sample], smax);        
    }

    Serial.print("min: ");
    Serial.print(smin);
    Serial.print(" max: ");
    Serial.print(smax);
    Serial.print("\n");

    delay(200);
    digitalWrite(LED_BUILTIN, 1);
    delay(200);
    digitalWrite(LED_BUILTIN, 0);
    Serial.flush();
}

void loop() {


    // take the sample

    sample_index = (sample_index + 1) % SAMPLES_COUNT;
    int sample = analogRead(IN_PIN);
    samples[sample_index] = sample;
    delayMicroseconds(SAMPLING_RATE_MICROSECONDS);
    // show that it's doing something
    // digitalWrite(LED_BUILTIN, (sample_index / 100) % 2);

    if (sample_index == (SAMPLES_COUNT - 1)) {
        dump();

        while (true) { delay(100); }
    }

    
}