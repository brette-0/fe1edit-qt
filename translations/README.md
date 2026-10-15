# FE1 translation patches — acquisition status

Scope: fan translation romhacks for *Fire Emblem: Ankoku Ryuu to Hikari no
Tsurugi* (NES). Target ROM for every entry below is the same:
No-Intro `Fire Emblem - Ankoku Ryuu to Hikari no Tsurugi (Japan)`,
ROM CRC32 `97CAD370`, ROM SHA-1 `DD1D51FF6D57E83F2BE0517F1DE821C85ABE86AE`.

## What is here

`metadata/` — full database records retrieved from romhack.ing (RHDI), the
successor database to romhacking.net. `metadata/index.json` is the summary.

| slug | author | ver | released | patch size | patch file |
|---|---|---|---|---|---|
| quirino-1.0 | Quirino | 1.0 | 2011-02-20 | 103868 B | NOT retrieved |
| polinym-1.4.1 | Polinym | 1.4.1 | 2026-05-20 | 37628 B | NOT retrieved |

## What is NOT here, and why

No patch binaries. Every distribution route for the patch files is behind an
access control the hosts put there deliberately:

- `romhacking.net` direct — HTTP 403, Cloudflare bot block.
- `romhack.ing` entry records — readable (that is where `metadata/` came
  from), but each record carries `hasCaptchaGatedContent: true` and an empty
  `fileUrl.url`. The binary is only released after a CAPTCHA.
- `romhack.ing` bulk — `robots.txt` is `User-agent: * / Disallow: /`, and the
  site's own scraping policy routes bulk retrieval through a Patreon-gated
  Consumer API key tied to one account holder.
- Internet Archive mirror `romhacking.net-20240801` (12.5 GB, has both a
  metadata SQL dump and the patch archive) — HTTP 401,
  `access-restricted-item: true`, collection includes `loggedin`.
- No author-hosted mirror: distribution for these runs through RHDN, not
  e.g. a project repo.

Getting the binaries means clearing one of those gates as yourself:

1. Open each `entryUrl` in a browser and solve the CAPTCHA (2 files).
2. Log in to archive.org and pull `romhacking.net-20240801`, which also
   contains the older translations (Gaijin Productions, DarknessSavior,
   Megakoopax) that are not in `metadata/` — see below.
3. Patreon-tier RHDI Consumer API key, if you want the whole database.

## Known incomplete

Older FE1 translations exist (Gaijin Productions ~2000, DarknessSavior 2007,
Megakoopax 2017). RHDI exposes no per-game or per-author content listing on
its no-JS routes and ignores search filter params, so enumerating them needs
the gated bulk API or the archive.org item. Only the two entries above were
reachable by direct record lookup.

Retrieved 2026-10-15.
