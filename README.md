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
Download https://www.segger.com/downloads/jlink/JLink_Linux_V630_x86_64.deb into `Downloads` directory
```
cd Downloads
sudo dpkg -i JLink_Linux_V630_x86_64.deb
rm JLink_Linux_V630_x86_64.deb
```
