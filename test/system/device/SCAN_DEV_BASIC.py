#!/usr/bin/env python3
import subprocess
import os
import sys
sys.path.append("../lib/")
sys.path.append("../start/")

import json_parser
import pos
import cli
import test_result
import START_POS_BASIC


def set_result(detail):
    code = json_parser.get_response_code(detail)
    result = test_result.expect_true(code)
    with open(__file__ + ".result", "w") as result_file:
        result_file.write(result + " (" + str(code) + ")" + "\n" + detail)

def execute():
    START_POS_BASIC.execute()
    out = cli.scan_device()
    return out

if __name__ == "__main__":
    test_result.clear_result(__file__)
    out = execute()
    set_result(out)
    pos.kill_pos()