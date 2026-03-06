#!/bin/bash
set -ex

docker run --rm -v "$(pwd)":/io quay.io/pypa/manylinux_2_34_x86_64 \
    /bin/bash -c '
    set -e
    for PYBIN in /opt/python/cp{311,312,313}*/bin; do
        "${PYBIN}/pip" wheel /io -w /tmp/wheels
    done
    auditwheel repair /tmp/wheels/*.whl -w /io/wheelhouse
'
