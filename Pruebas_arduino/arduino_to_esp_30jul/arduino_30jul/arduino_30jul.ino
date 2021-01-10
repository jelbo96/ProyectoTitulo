void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.write("Hello from arduino");
    delay(2000);
}
