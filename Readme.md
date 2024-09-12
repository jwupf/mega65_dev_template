# MEGA65 DevEnv

## SSH key sharing

On the host run `ssh-add $HOME/.ssh/id_rsa`(assuming id_rsa is your key for accessing git repo) to add the key to the ssh agent. That way, it is automagically forwardet into the devcontainer.

## X11/Wayland forwarding

Run `xhost +local:docker` before starting vscode if you want to start X11 apps from within the container.

## XEMU build and installation

```bash
sudo apt install alien fakeroot
git clone https://github.com/lgblgblgb/xemu.git
cd xemu
build
build deb
# adapt version number if needed
dpkg -i build/bin/xemu_20240807161529_amd64.deb 
```


Autostart a disk image with xemu-xmega65:
`xemu-xmega65 -8 main.d81 -autoload`

## building

If building in VsCode with cmake extension, use "__unspec__" Kit, then the Cmake: Configure will figure it out.