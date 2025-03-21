#!/bin/sh

# Copyright (C) 2020 Intel Corporation. All rights reserved.
# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

/usr/bin/env python -m pip install --user -r ../build-scripts/requirements.txt
/usr/bin/env python ../build-scripts/build_llvm.py "$@"
