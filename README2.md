TODO clean this readme....

If you want to edit the UI file with Qt Designer (not Qt Design Studio!), install:
```console
sudo apt-get install qttools5-dev-tools
```
![image](https://github.com/MorgesHAB/ERT2023GS/assets/28660469/e7324286-9fd2-4640-bcdb-285780499c3a)


With WSL1 !!! because really better ! serial port forwarding with Qt
And also with WSL1 IP port forward is not necessary !!

Simply do: once installed
```
sudo influxd &
sudo grafana-server -homepath /usr/share/grafana &
```

Then connect directly with the IP address:
http://172.22.22.141:3000/login
http://172.22.22.141:8086/signin

otherwise simply use:
```
bash start_influxDB_Grafana.sh
```
Once finish
```
bash stop_influxDB_Grafana.sh
```

___________________________________________
# Install from zero (PC2)
install WSL
No need to go to the Windows market place, simply run that in Powershell admin:
```
wsl --install
```
Restart your computer
It will open automatically a Ubuntu window writing: "setup ongoing" (?)
Insert a username and password

On WindowsPowershell, check if you have WSL 2, please change to 1 for Serial port
```
wsl -l -v
```
```
wsl --set-version Ubuntu 1
```
It tooks 1min on my new PC


## Install ERTGS2023 Qt UI App
```console
sudo apt-get update
```
```console
sudo apt-get upgrade
```
Now we need to install cmake to compile the code
```console
sudo apt-get install cmake
```
Install git to be able to clone this git repository
```console
sudo apt-get install git
```
Run the following command as sudo in order to get needed packages before installing Qt5
```console
sudo apt-get install build-essential
```

```console
git clone --recursive-submodules https://github.com/MorgesHAB/ERT2020GS.git
```

This is no more available 
```console
sudo apt-get install qt5-default
```
So do that (this package is sufficient to compile this App):
```console
sudo apt-get install qtbase5-dev
```
Necessary to communicate with RF device
```console
sudo apt-get install libqt5serialport5-dev
```
Optionnally if want to play some sound
```console
sudo apt-get install qtmultimedia5-dev
```
On Linux/Ubuntu, you are done! 
you can run the App as follow:
```console
mkdir build && cd build
cmake ..
make Nordend
./Nordend
```

However on Windows (WSL), it's when the awful part comes in play:
Because of a Qt bug issue, you need to run that:
```console
sudo strip --remove-section=.note.ABI -tag /lib/x86_64-linux-gnu/libQt5Core.so.5
```
If it does not find the file, run that to find the path:
```console
ldconfig -p | grep "libQt5Core.so.5"
```

Now as WSL1 does not provide UI, you need to install a tool, this one work:
https://sourceforge.net/projects/vcxsrv
Then set the display:
```console
export DISPLAY=:0
```
Then run!
```console
./XSTRATO
```
___________________________________________


# WSL 2

Step 1: Go to settings > (search) turn windows feature on / off
Step 2: If Windows Hypervisor Platform and Windows Machine Platform is unchecked, please check them, else uncheck and recheck them.
Step 3: Reboot
https://github.com/microsoft/WSL/issues/8693

Upgrade version from WSL 1 to WSL 2, as WSL2 now supports GUI
```
sudo apt update
sudo apt full-upgrade
```

on PowerShell
```
wsl --install
wsl --set-version Ubuntu 2
```
This might take few hours !

`wsl -l -v`
NAME      STATE           VERSION
* Ubuntu    Stopped         2


___________________________________________
## Install InfluxDB
```
wget https://dl.influxdata.com/influxdb/releases/influxdb2-2.7.1-amd64.deb
sudo dpkg -i influxdb2-2.7.1-amd64.deb
```
Do *not* run: sudo apt-get install influxdb


On WSL Ubuntu, you can manually run the InfluxDB daemon with:
influxd &
The ampersand at the end makes the daemon run in the background, so you can still execute commands after launching it. You can also close the WSL window, and the daemon will keep running.

Note: you can accidently run multiple instances of the InfluxDB with this method; you can check that none is running with:
ps -A | grep influxd
```
sudo influxd &
```
Go to localhost:8086

To stop the background process
```
sudo pkill influxd
```
You can check it really kill the process by running `ps -A | grep "influx"`

On windows powershell run in administartor
netsh interface portproxy add v4tov4 listenport=8086 listenaddress=0.0.0.0 connectport=8086 connectaddress=172.31.112.228
netsh interface portproxy show all

New-NetFirewallRule -DisplayName "WSL2 Port Bridge" -Direction Inbound -Action Allow -Protocol TCP -LocalPort 8086

Tuto: https://jwstanly.com/blog/article/Port+Forwarding+WSL+2+to+Your+LAN/

# Grafana

```
sudo apt-get install -y adduser libfontconfig1
wget https://dl.grafana.com/enterprise/release/grafana-enterprise_9.5.1_amd64.deb
sudo dpkg -i grafana-enterprise_9.5.1_amd64.deb
```
```
sudo grafana-server -homepath /usr/share/grafana &
```
The default username and password for Grafana is admin / admin . The first time you login, you will be asked to reset the default admin password.
Now: admin pwd: B***
```shell
netsh interface portproxy add v4tov4 listenport=3000 listenaddress=0.0.0.0 connectport=3000 connectaddress=172.31.112.228
New-NetFirewallRule -DisplayName "WSL2 Port Bridge" -Direction Inbound -Action Allow -Protocol TCP -LocalPort 3000
```

## InfluxDB-CXX-

If before you need to update your cmake version like me:
```
wget https://github.com/Kitware/CMake/releases/download/v3.26.3/cmake-3.26.3.tar.gz
tar -xvf cmake-3.26.3.tar.gz
cd cmake-3.26.3/
./configure
make
sudo make install
```
 
before again install cpr (-DCPR_USE_SYSTEM_CURL=ON is important!)
https://github.com/libcpr/cpr
```shell
git clone https://github.com/libcpr/cpr.git
cd cpr && mkdir build && cd build
cmake .. -DCPR_USE_SYSTEM_CURL=ON
cmake --build .
sudo cmake --install .
```

InfluxDB (Catch2 lib is for TEST)
cmake -D cpr_DIR=/usr/local/lib/cmake/cpr -D INFLUXCXX_TESTING:BOOL=OFF -D INFLUXCXX_WITH_BOOST=OFF ..
cmake -D INFLUXCXX_TESTING:BOOL=OFF ..

https://github.com/offa/influxdb-cxx
try using TCP and not HTTP!
TCP	boost	tcp	tcp://localhost:8094


wget https://launchpad.net/ubuntu/+archive/primary/+files/libboost-dev_1.71.0.0ubuntu2_amd64.deb



-------------------
if want to uninstall all the influxDB stuff.
in /root/
rm -rf .influxdbv2/

sudo dpkg -r influxdb2     (remove)
sudo dpkg -P influxdb2     (purge)

sudo service influxdb stop
sudo apt remove influxdb
sudo apt remove influxdb-client
sudo apt remove influxdb2
sudo apt autoclean && sudo apt autoremove

sudo rm -rf /var/lib/influxdb/
sudo rm -rf /var/log/influxdb/
sudo rm -rf /etc/influxdb/
sudo rm -rf ~/.influxdbv2/configs


-------------------------
## How to setup project on VScode
```
git config --global user.name "Lionel-NUC"
git config --global user.email johndoe@example.com
git config pull.rebase false
```
The last command set to merge by default when pull-push problem (vs rebase, ...)
