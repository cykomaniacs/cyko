# **CYKO** - CXX ToolKit

> *Found some old code from 2012 on my "cloud".*\
> *Decided to use it as base for a toolkit.*
>
> > *June 2022*
>
> **@[eggheadedmonkey](https://github.com/eggheadedmonkey)**

# **GitHub Codespaces Instructions**

> Assumes your container runs **Debian**.

## **BUILD DEPENDENCIES**

- [**`CLANG`**](#clang)
- [**`POWERSHELL`**](#powershell)

### **POWERSHELL**

> Setup the base environment

```sh
# fetch latest package meta-data
sudo apt update
# fetch necessary utilities
sudo apt install curl
```

> Setup the repositories

```sh
# add microsofts gpg keys (important!)
curl https://packages.microsoft.com/keys/microsoft.asc \
  | sudo apt-key add -

# add microsofts sources/feeds
sudo echo 'deb [arch=amd64] https://packages.microsoft.com/repos/microsoft-debian-bullseye-prod bullseye main' \
  > /etc/apt/sources.list.d/microsoft.list
```

> Setup the package

```sh
# fetch latest package meta-data (including the new sources/feeds)
sudo apt update
# fetch and install...
sudo apt install powershell
```

</br>

> <sub>*Read about more methods here...*</sub>\
> <sup>*https://docs.microsoft.com/en-us/powershell/scripting/install/install-debian*</sup>

---

## **License**

[**CYKO**](https://github.com/cykomaniacs/cyko)
is a **free** and **open-source** project distributed under the terms of the
MIT License. A short and simple permissive license with conditions only
requiring preservation of copyright and license notices.

> *See the [LICENSE](LICENSE) file for details.*

<!--
https://github.com/cykomaniacs/cyko/blob/main/README.md?plain=1#L26
[POWERSHELL](https://github.com/cykomaniacs/cyko#powershell)
-->
