# Source of Trust
## Desc
> Author: ariaf

Sebuah halaman login sederhana milik member area masih menyimpan catatan staging di source HTML. Temukan akun tomoya yang tertinggal, lalu gunakan akun tersebut untuk masuk dan mengambil flag.

> Target: http://localhost:8081

## Chall
### Run
```bash
docker compose up --build
```

Buka service di:

```text
http://localhost:8081
```

## Solution
Pertama, buka halaman login seperti biasa. Karena chall ini mengarah ke web basic enumeration, cek source halaman dengan `View Page Source` atau request halaman dari terminal.

```bash
curl http://localhost:8081/
```

Di dalam HTML terdapat komentar staging yang membocorkan credential tomoya.

```html
<!-- staging note: tomoya account => username: tomoya | password: letmein99 -->
```

Gunakan credential tersebut pada form login.

```text
username: tomoya
password: letmein99
```

Setelah login berhasil, halaman member area akan menampilkan flag.

Alternatif via `curl`:

```bash
curl -i -c cookies.txt -d "username=tomoya&password=letmein99" http://localhost:8081/
curl -b cookies.txt http://localhost:8081/
```

## Flag
NFCTF{v13w_s0uRc3_th3n_l0g1n}
