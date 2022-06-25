# **CYKO** - CXX ToolKit

> *Found some old code from 2012 on my "cloud".*\
> *Decided to use it as base for a toolkit.*
>
> > *June 2022*
>
> **@[eggheadedmonkey](https://github.com/eggheadedmonkey)**

## **GitHub Codespaces Instructions**

> `assumes your container runs debian`

### **BUILD DEPENDENCIES**

---

**`CLANG`** - **`POWERSHELL`**

---

### **POWERSHELL**

---

`setup base environment`

```sh
# fetch latest package meta-data
sudo apt update
# fetch necessary utilities
sudo apt install curl
```

`setup repositories`

```sh
# add microsofts gpg keys (important!)
curl https://packages.microsoft.com/keys/microsoft.asc \
  | sudo apt-key add -

# add microsofts sources/feeds
sudo echo 'deb [arch=amd64] https://packages.microsoft.com/repos/microsoft-debian-bullseye-prod bullseye main' \
  > /etc/apt/sources.list.d/microsoft.list
```

`setup package`

```sh
# fetch latest package meta-data (including the new sources/feeds)
sudo apt update
# fetch and install...
sudo apt install powershell
```

</br>

> *Read about more methods here...*\
> *https://docs.microsoft.com/en-us/powershell/scripting/install/install-debian*

---

<!--
https://github.com/cykomaniacs/cyko/blob/main/README.md?plain=1#L26
[POWERSHELL](https://github.com/cykomaniacs/cyko#powershell)
-->
