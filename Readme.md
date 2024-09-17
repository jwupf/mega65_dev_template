# MEGA65 DevEnv

## RAM limitations

Building llvm needs a lot of RAM ... 
Change the `-j` option in line 13 ```	ninja -j 6)``` if you have more than 8 GB of RAM. Every compile process needs RAM. If the system runs out of RAM it will hang the computer.
On a RaspberryPi with 8GB, use `-j 3` and get a thermos of tea :-)

## SSH key sharing

On the host run `ssh-add $HOME/.ssh/id_rsa`(assuming id_rsa is your key for accessing git repo) to add the key to the ssh agent. That way, it is automagically forwardet into the devcontainer.
Add it to ~/.profile to have this as default.

## XEMU build and installation

```bash
sudo apt install alien fakeroot libsdl2-dev libreadline-dev
git clone https://github.com/lgblgblgb/xemu.git
cd xemu
build
build deb
# adapt version number if needed
dpkg -i build/bin/xemu_20240807161529_amd64.deb 
```


Autostart a disk image with xemu-xmega65:
`xemu-xmega65 -autoload -8 main.d81`

## building

If building in VsCode with cmake extension, use "__unspec__" Kit, then the Cmake: Configure will figure it out.

## Docker

```bash
sudo apt install docker.io
sudo usermod -a -G docker $USER

```