FROM debian:bookworm-slim AS builder

RUN apt-get update \
    && apt-get install -y --no-install-recommends gcc libc6-dev binutils \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build
COPY chall.c .

RUN gcc chall.c -o chall \
      -O0 \
      -Wall -Wextra \
      -fPIE -pie \
      -fstack-protector-strong \
      -Wl,-z,relro,-z,now \
    && strip chall

FROM debian:bookworm-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends socat \
    && rm -rf /var/lib/apt/lists/* \
    && useradd -m -u 1000 ctf

COPY --from=builder /build/chall /home/ctf/chall
COPY flag.txt /flag.txt

RUN chown root:root /flag.txt /home/ctf/chall \
    && chmod 444 /flag.txt \
    && chmod 555 /home/ctf/chall

USER ctf
WORKDIR /home/ctf

EXPOSE 1337

CMD ["socat", "TCP-LISTEN:1337,reuseaddr,fork", "EXEC:/home/ctf/chall,stderr"]
