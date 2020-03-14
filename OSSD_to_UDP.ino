#include <UIPEthernet.h>
#include <utility/logging.h>

EthernetUDP udp;

const int OSSDpin1 = 5;
const int OSSDpin2 = 6;

boolean ossd1;
boolean ossd2;

boolean ossd_triggered = false;

void setup() {
  // put your setup code here, to run once:

  pinMode(OSSDpin1, INPUT_PULLUP);
  pinMode(OSSDpin2, INPUT_PULLUP);

  Serial.begin(9600);

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};

  Ethernet.begin(mac,IPAddress(10,0,0,3));

}

void loop() {

  int udpMessage;

  ossd1 = digitalRead(OSSDpin1);
  //Serial.println(ossd1);
  ossd2 = digitalRead(OSSDpin2);
  //Serial.println(ossd2);

  if(ossd1 == true && ossd2 == true){
    ossd_triggered = true;
  }
  else{
    ossd_triggered = false;
  }

  if(ossd_triggered == true){
    udpMessage = udp.beginPacket(IPAddress(10,0,0,1),6792);
    udpMessage = udp.write("triggered");
    udpMessage = udp.endPacket();
    udpMessage = udp.parsePacket();
  }
  else{
    udpMessage = udp.beginPacket(IPAddress(10,0,0,1),6792);
    udpMessage = udp.write("not triggered");
    udpMessage = udp.endPacket();
    udpMessage = udp.parsePacket();
  }
  Serial.println(ossd_triggered);
}
