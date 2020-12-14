#! /usr/bin/env python3
import subprocess
import json
import argparse
import sys

def main():
    parser = argparse.ArgumentParser()
    parser.description = u'Compile test a sketch for all available boards'
    parser.add_argument(u'-s', u'--sketch', dest=u'sketch',
                        required=True, help=u'Path to sketch')
    args = parser.parse_args()
    test_all_boards(args.sketch);

def test_all_boards(sketch):
    process = subprocess.run("arduino-cli board listall --format json".split(),stdout=subprocess.PIPE)
    board_list_json = process.stdout.decode('utf-8')
    board_list = json.loads(board_list_json)
    start = True
    exlude = ["arduino:samd:tian_cons","arduino:avr:gemma"]
    for board in board_list['boards']:
        if board['FQBN'] in exlude:
            continue;
        else:
            print(board['FQBN'])
            command = "arduino-cli compile --fqbn {board} {sketch}".format(board=board['FQBN'], sketch=sketch)
            process = subprocess.run(command.split(),stdout=subprocess.PIPE)
            if process.returncode:
                print(process.stdout.decode('utf-8'))
                sys.exit(process.returncode)




if __name__ == '__main__':
    main()
