# **`cyko`** cxx toolkit

## **GitHub Codespaces Instructions**

> `assumes that your container runs the latest **debian** release.`

### **BUILD DEPENDENCIES**

---

**`CLANG`** - **`POWERSHELL`**

---

### **`POWERSHELL`**

Prepare

  ```sh
  # udate package sources
  sudo apt update
  # setup necessary tools
  sudo apt install curl
  ```

Configure

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

Install

  ```sh
  sudo apt install powershell
  ```

</br>

> Microsofts guide:</br>
> https://docs.microsoft.com/en-us/powershell/scripting/install/install-debian

---
