#! /bin/sh
export PROXYDIR=$FILES/RunII/FARM/inputs/x509_user_proxy
mkdir -p $PROXYDIR; voms-proxy-init --voms cms             -valid 720:00 --out $PROXYDIR/x509_proxy
export X509_USER_PROXY=$PROXYDIR/x509_proxy;