# **CYKO** - CXX ToolKit

## **GitHub Codespaces Instructions**

> `assumes that your container runs the latest debian release.`

### **BUILD DEPENDENCIES**

---

**`CLANG`** - **`POWERSHELL`**

---

### **POWERSHELL**

##### PREPARE

  ```sh
  # udate package sources
  sudo apt update
  # setup necessary tools
  sudo apt install curl
  ```

##### CONFIGURE

  ```sh
  # add microsofts gpg keys (important!)
  curl https://packages.microsoft.com/keys/microsoft.asc \
    | sudo apt-key add -

  # add microsofts source/feed
  sudo echo 'deb [arch=amd64] https://packages.microsoft.com/repos/microsoft-debian-bullseye-prod bullseye main' \
    > /etc/apt/sources.list.d/microsoft.list

  # update package sources (includes the new source/feed)
  sudo apt update
  ```

##### INSTALL

  ```sh
  sudo apt install powershell
  ```

</br>

> Microsofts guide:\
> https://docs.microsoft.com/en-us/powershell/scripting/install/install-debian

---

<!--
https://github.com/cykomaniacs/cyko/blob/main/README.md?plain=1#L26
[POWERSHELL](https://github.com/cykomaniacs/cyko#powershell)
-->
