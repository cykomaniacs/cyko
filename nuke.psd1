@{
# information (about, authors, version, etc...)
info = @{
  description = "Generic build cleaner for Windows"
  summary = "build cleaner"
  # --------------------------------
  # .number: major.minor.patch
  #   .name: codename
  # --------------------------------
  version = @{ number = "0.1.4"; name = "namespacer" }
  # --------------------------------
  # .name: ...
  # .home: web url
  # .mail: contact email
  # --------------------------------
  author = @{
    name = "eggheadedmonkey"
    home = "https://github.com/eggheadedmonkey"
    mail = "cyko@eggheadedmonkey.com"
  }
  # --------------------------------
  # .name: ...
  # .home: web url
  # .mail: contact email
  # --------------------------------
  organization = @{
    name = "cykomaniacs"
    home = "https://github.com/cykomaniacs"
    mail = "cyko@eggheadedmonkey.com"
  }
}
# timestamps
date = @{ created = "2022/06/14"; updated = "2022/06/21" }
# repository url
repo = "https://github.com/cykomaniacs/cyko"
# dry-run (don't do anything, just print)
fake = $false
# ignored files (ie. don't delete)
keep = @(
  ".gitkeep"
)
}
