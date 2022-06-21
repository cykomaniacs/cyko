#!/bin/sh
#----------------------------------------
#@ https://docs.microsoft.com/en-us/powershell/scripting/install/install-debian
#@ /etc/apt/sources.list.d/microsoft.list
#----------------------------------------
#deb [arch=amd64 signed-by=/usr/share/keyrings/microsoft-archive-keyring.gpg] https://packages.microsoft.com/repos/microsoft-ubuntu-focal-prod focal main
#deb [arch=amd64] https://packages.microsoft.com/repos/microsoft-debian-bullseye-prod bullseye main
#----------------------------------------

curl https://packages.microsoft.com/keys/microsoft.asc | sudo apt-key add -
