import argparse
import asyncio

from api_keys import API_WRITE
from remote import RemoteIotThing, IotLabWriteModel


def define_arg_parser():
    parser = argparse.ArgumentParser()
    parser.add_argument('--water-level', dest='water_level', type=int)
    parser.add_argument('--pressure', type=int)
    parser.add_argument('--pump-state', dest='pump_state', type=int)

    return parser


async def main():
    args = define_arg_parser().parse_args()
    data = IotLabWriteModel(
        water_level = args.water_level,
        pressure = args.pressure,
        pump_state = args.pump_state
    )

    remote = RemoteIotThing(api_write=API_WRITE)
    await remote.send_lab_data(data)

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
