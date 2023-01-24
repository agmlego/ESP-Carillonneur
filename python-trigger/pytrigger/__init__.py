from builtins import bytes

from optparse import OptionParser
import logging
import select
import sys
import time

import pymidi.client
from pymidi.protocol import DataProtocol, ControlProtocol
from pymidi import utils
from pymidi.packets import MIDINote

try:
    import coloredlogs
except ImportError:
    coloredlogs = None

from .finder import find_servers

logger = logging.getLogger('trigger')

APPLEMIDI = '_apple-midi._udp.local.'
DEFAULT_BIND_ADDR = '0.0.0.0:5051'

parser = OptionParser()
parser.add_option(
    '-b',
    '--bind_addr',
    dest='bind_addrs',
    action='append',
    default=None,
    help='<ip>:<port> for listening; may give multiple times; default {}'.format(DEFAULT_BIND_ADDR),
)
parser.add_option(
    '-v', '--verbose', action='store_true', dest='verbose', default=False, help='show verbose logs'
)


def iter_note_names():
    yield from MIDINote.ksymapping.values()


def main():
    options, args = parser.parse_args()

    log_level = logging.DEBUG if options.verbose else logging.INFO
    if coloredlogs:
        coloredlogs.install(level=log_level)
    else:
        logging.basicConfig(level=log_level)

    client = pymidi.client.Client()
    addr, port = next(find_servers(APPLEMIDI))
    logger.info(f'Connecting to RTP-MIDI server @ {addr}:{port} ...')
    client.connect(str(addr), port)
    logger.info('Connecting!')
    for note in iter_note_names():
        logger.info(f'Striking {note}...')
        client.send_note_on(note)
        time.sleep(0.2)
        client.send_note_off(note)

