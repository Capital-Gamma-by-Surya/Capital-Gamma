# Capital-Gamma

#### Setting up Docker for local runs
`docker build --no-cache -t <user-name>/<build-name>:<tag> .`

`docker push <user-name>/<build-name>:<tag>`

`act -P ubuntu-latest=<user-name>/<build-name>:<tag>`
