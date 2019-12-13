import asyncio

from api_keys import API_READ
from remote import RemoteIotThing


async def main():
    remote = RemoteIotThing(api_read=API_READ)
    while True:
        await asyncio.sleep(10)

        async for feed in remote.read_lab_data():
            print(feed)


if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(main())
