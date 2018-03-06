# Microbit lab TTK4235

## Setup
### Install arm gcc compiler
```
sudo apt install gcc-arm-none-eabi
```

### Install nrfjprog
```
curl https://www.nordicsemi.com/eng/nordic/download_resource/58852/27/77161598/94917 | tar xv
sudo chown root:root -R nrfjprog/*
sudo mv nrfjprog/* /usr/bin && rm -d nrfjprog
```

### Install JLinkArm
```
cd setup
sudo dpkg -i JLink_Linux_V630_x86_64.deb
```

### Remove DAL
* Hold down reset on the microbit
* Copy `JLink_OB_BBC_microbit_17-03-24.hex` from setup onto the microbit
```
nrfjprog -f nrf51 -e
```
* The led matrix on the microbit will then turn off
