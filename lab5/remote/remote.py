from typing import Dict

import requests_async as requests
import json


class Remote:
	def __init__(self, api_read: str = None, api_write: str = None):
		self._api_read = api_read
		self._api_write = api_write

	async def read(self):
		async with requests.Session() as session:
			response = await session.get(self._api_read)
			return json.loads(response.content)

	async def write(self, values: Dict[str, str]):
		url = self._api_write
		for key, value in values.items():
			if key and value:
				url += "&{0}={1}".format(key, value)

		async with requests.Session() as session:
			await session.get(url)


class IotLabWriteModel:
	def __init__(self, water_level, pressure, pump_state):
		self.water_level = water_level
		self.pressure = pressure
		self.pump_state = pump_state


class ThingsKeepFeedModel:
	def __init__(self, water_level, pressure, pump_state, created_at):
		self.water_level = water_level
		self.pressure = pressure
		self.pump_state = pump_state
		self.created_at = created_at

	def __str__(self):
		return ', '.join((
			f'water-level: {self.water_level}',
			f'pressure: {self.pressure}',
			f'pump-state: {self.pump_state}',
			f'created_at: {self.created_at}',
		))


class RemoteIotThing(Remote):
	async def send_lab_data(self, data: IotLabWriteModel):
		await self.write({
			'field1': data.water_level,
			'field2': data.pressure,
			'field3': data.pump_state,
		})

	async def read_lab_data(self):
		data = await self.read()

		for feed in data['feeds']:
			yield ThingsKeepFeedModel(
				water_level=feed['field1'],
				pressure=feed['field2'],
				pump_state=feed['field3'],
				created_at=feed['created_at']
			)
