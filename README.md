# Det intelligente hus

<!-- Indholdsfortegnelse -->
<details open="open">
  <summary>Indholdsfortegnelse</summary>
  <ol>
    <li>
      <a href="#om-projektet">Om projektet</a>
    </li>
    <li>
      <a href="#features">Features</a>
    </li>
    <li>
      <a href="#setup">Setup</a>
      <ul>
        <li><a href="#krav">Krav</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#licens">Licens</a></li>
    <li><a href="#kontakt">Kontakt</a></li>
  </ol>
</details>

<!-- Om projektet -->
## Om projektet
Formålet med Det intelligente Hus er at optimere energiforbruget samt give en bedre oplevelse for husets beboere, ved hjælp af automatisering of fjernstyring af enheder i hjemmet

<!-- Features -->
## Features
### RFID kort til åbning af hoveddør
Rfid chippen scanner koden fra kortet, Board 2 publisher det så til Thingspeak brokeren via MQTT på det angivne topic(channels/1559675), hvor Board 1 har en subscription.
Board 1 modtager koden fra Thingspeak brokeren via MQTT og sender det direkte videre til MEGA 2560 boardet over Wire.(I2C)

<!-- Setup -->
### Setup
![Diagram](https://github.com/gamingAmee/Det-intelligente-hus/blob/master/images/Untitled%20Diagram.drawio.png)


<!-- Krav -->
#### Krav
##### Hardware
* Atmel mega2560
* 2x MKR WIFI 1010
* Servo SG90
* 2x RGB LED
* RFID Kort
* Level converter(3,3v-5v / 5v-3,3v)
* Photoresistor
* Kabler

##### Software
* Visual studio code m/ PlatformIO til kodning af MKR WIFI 1010
* Microchip studio til kodning af Atmel mega2560

<!-- Installation -->
#### Installation
#### Libraries
##### Board 1
* Adafruit BusIO
* Adafruit GFX Library
* Adafruit SSD1306
* MQTT
* WIFININA

##### Board 2
* MQTT
* WiFiNINA
* MFRC522
* 
##### Mega
* Wire
* Servo
* SPI

<!-- Licens -->
### Licens
MIT licens

<!-- Kontakt -->
### Kontakt
- [x] Vær den bedste
