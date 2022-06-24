# **`cyko`** - `cxx toolkit`
## **CODESPACE INSTRUCTIONS**

</br>

> assumes that you run **debian** *(latest release)*.

</br>

### **BUILD DEPENDENCIES**

---

#### **`POWERSHELL`**

</br>

> Microsofts guide:</br>
> https://docs.microsoft.com/en-us/powershell/scripting/install/install-debian

</br>

+ `preparations`

```Shell
sudo apt update
sudo apt install curl
```

+ `repository gpg keys`

> ```Shell
> curl https://packages.microsoft.com/keys/microsoft.asc | sudo apt-key add -
> ```

+ `repository sources/feeds`

```Shell
# apt-sources: add
sudo echo 'deb [arch=amd64] https://packages.microsoft.com/repos/microsoft-debian-bullseye-prod bullseye main' > /etc/apt/sources.list.d/microsoft.list
# apt-sources: update
sudo apt update
```

+ `installation`

```shell
sudo apt update
sudo apt install powershell
```
