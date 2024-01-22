import asyncio
import aiogram
import os
from aiogram import Bot, Dispatcher ,types, enums 
from aiogram.types import Message ,Video , Audio
from aiogram.types import ReplyKeyboardMarkup, KeyboardButton, InlineKeyboardMarkup, InlineKeyboardButton
from aiogram.filters import Command
from search import *
from main_bd import *
from aiogram import F
from aiogram.filters import StateFilter
from aiogram.fsm.context import FSMContext
from aiogram.fsm.state import StatesGroup, State
from aiogram.fsm.context import FSMContext

token = '5577625193:AAGBtQsZAaBKJk9nUSUUJGfwuMZDfk89Gv8'
admin_chat_id = "907267780"
dp = Dispatcher()

bot = Bot(token)
class  order(StatesGroup):
	document = State()
	video = State()
	web = State()
	void = State()

@dp.message(Command("start") )
async def start (message: Message):
	await bot.send_message(chat_id = message.chat.id , text = 'hello my client')
@dp.message(Command("search"))
async def searching(message: Message):
	await bot.send_message(chat_id = message.chat.id , text = "se:")
@dp.message(Command("recommend") )
async def recommend(message: Message):
	b = []
	b.append([InlineKeyboardButton(text = "Book" , callback_data = f"rec||document")])
	b.append([InlineKeyboardButton(text = "Webside" , callback_data = f"rec||web")])
	b.append([InlineKeyboardButton(text = "Video" , callback_data = f"rec||video")])
	markup = InlineKeyboardMarkup(inline_keyboard = b)
	await bot.send_message(
		chat_id = message.chat.id, 
		text = "Select your recommendation type:",
		reply_markup = markup)



async def main_menu(message: Message, txt: str):	
	text = txt
	#print(text)
	video = []
	document = []
	website = []
	index = search(text)
	if len(index) == 0:
		await bot.send_message(chat_id = message.chat.id , text = "Invalid Request | Неправильный запрос")
		return
	for i in index:
		try:
			#video_inf(i)
			Video = [InlineKeyboardButton(text = 'Video', callback_data = f'video||{text}')]
			continue
		except:
			pass

		try:
			#document_inf(i)
			document = [InlineKeyboardButton(text = 'Books', callback_data = f'document||{text}')]
			continue
		except:
			pass
		try:
			#web_inf(i)
			website = [InlineKeyboardButton(text = 'website', callback_data = f'web||{text}')]
			continue
		except:
			pass

	try:
		back =  InlineKeyboardButton(text = 'res:1080p', callback_data = f'oheg')
		forward =  InlineKeyboardButton(text = 'res:1080p', callback_data = f'oheg')
		video =  InlineKeyboardButton(text = 'Video', callback_data = f'video||{text}')
		audio =  InlineKeyboardButton(text = 'audio', callback_data = f'audio||{text}')
		web =  InlineKeyboardButton(text = 'web', callback_data = f'web||{text}')

		stream = InlineKeyboardMarkup( inline_keyboard = [Video, document, website])
		await bot.send_message(chat_id = message.chat.id , text = "Select format" , reply_markup = stream)
		await bot.delete_message(message.chat.id,message.message_id)
	except Exception as e:
		await bot.send_message(chat_id = message.chat.id , text = f'{e}')

@dp.callback_query(lambda c: list(c.data.split('||'))[0] ==  "video")
async def video(callback_query : types.CallbackQuery):
	print("callback_query: ", list(callback_query.data.split()))
	a, text = callback_query.data.split('||')
	print("Text: ", text)
	index  = search(text)
	b = []
	i = index[0]
	video = video_inf(i)
	print("Video: ", video)

	nex = InlineKeyboardButton(text = "Next" , callback_data = f"next||video||1||{text}" )
	if len(index) > 1:
		b.append([nex])
	b.append([InlineKeyboardButton(text = "Download" , callback_data = f"download||{index[0]}")])
	b.append([InlineKeyboardButton(text = "BAck to menu" , callback_data = f"menu||{text}")])
	stream = InlineKeyboardMarkup(inline_keyboard = b)
	photo = types.input_file.FSInputFile(f'{video[1]}')

	#await bot.delete_message(callback_query.message.chat.id,callback_query.message.message_id )
	await bot.send_photo(chat_id = callback_query.message.chat.id,
						photo = photo,
						caption = list(list((video[0]).split("/"))[-1].split('.'))[0],
						reply_markup = stream,)
	await bot.delete_message(callback_query.message.chat.id,callback_query.message.message_id )


@dp.callback_query(lambda c: list(c.data.split('||'))[0] == 'next')
async def next(callback_query : types.CallbackQuery ):
	n, t, p, text = callback_query.data.split('||')
	p = int(p)
	print("P = ", p)
	index = search(text)
	print("Index: ", index)
	b = []
	nex = InlineKeyboardButton(text = "Next", callback_data = f"next||video||{p + 1}||{text}")
	back  = InlineKeyboardButton(text = 'Back' , callback_data = f"next||video||{p - 1}||{text}")
	if len(index) > p + 1:
		b.append([nex])
	if p > 0:
		b.append([back])
	b.append([InlineKeyboardButton(text = "Download" , callback_data = f"download||{index[p]}")])
	b.append([InlineKeyboardButton(text = "BAck to menu" , callback_data = f"menu||{text}")])
	stream = InlineKeyboardMarkup(inline_keyboard = b)
	video = video_inf(index[p])
	print(video)
	#photo = f'C:/Users/chron/OneDrive/Рабочий стол/qe/{video[1]}'
	photo = f'{video[1]}'
	photo = types.input_file.FSInputFile(photo)
	phot = types.input_media_photo.InputMediaPhoto(type = enums.input_media_type.InputMediaType.PHOTO, media = photo,caption = list(list((video[0]).split("/"))[-1].split('.'))[0],) #, caption = f'{video[0]}')
	await bot.edit_message_media( 
		chat_id = callback_query.message.chat.id,
		message_id = callback_query.message.message_id,
		media = phot,
		reply_markup = stream)

@dp.callback_query(lambda c: list(c.data.split('||'))[0] == 'menu')
async def menu(callback_query : types.CallbackQuery ):
	a, text = callback_query.data.split('||')
	print(type(callback_query.message))
	await main_menu(callback_query.message,text)


@dp.callback_query(lambda c: list(c.data.split('||'))[0] == 'rec')
async def rec(callback_query : types.CallbackQuery,state: FSMContext ):
	rec,type = callback_query.data.split("||")

	await bot.send_message(chat_id = callback_query.message.chat.id, text = "Upload a file or enter a link to it")
	if type == "video":
		await state.set_state(order.video)
		print("State video")
	elif type == "document":
		await state.set_state(order.document)
		print("State doc")
	else:
		await state.set_state(order.web)
		print("State web")
	await bot.delete_message(callback_query.message.chat.id,callback_query.message.message_id )

@dp.message(order.video ,F.content_type.in_({"text","video"}))
async def videorec(message: Message, state: FSMContext):
	await bot.send_message(chat_id = message.chat.id, text = "Thank you. your recommendation will be reviewed by the administrator and then added")
	await bot.forward_message(chat_id = admin_chat_id , from_chat_id = message.chat.id,message_id = message.message_id)
	await bot.send_message(chat_id = admin_chat_id, 
		text =f"""     Video
		message_id: {message.message_id}
		chat_id: {message.chat.id}
		Username {message.from_user.username}
		First_name: {message.from_user.first_name}
		Last_name: {message.from_user.last_name}
		Language: {message.from_user.language_code}
		Id: {message.from_user.id}""")
	await state.clear()

@dp.message(order.video )
async def videorec(message: Message, state: FSMContext):
	b = []
	b.append([InlineKeyboardButton(text = "Cancel", callback_data = "cancel")])
	markup = InlineKeyboardMarkup(inline_keyboard = b)
	await bot.send_message(chat_id = message.chat.id,
		text = "repeat your request or click cancel",
		reply_markup = markup)

@dp.message(order.web ,F.content_type.in_({"text"}))
async def videorec(message: Message, state: FSMContext):
	await bot.send_message(chat_id = message.chat.id, text = "Thank you. your recommendation will be reviewed by the administrator and then added")
	await bot.forward_message(chat_id = admin_chat_id , from_chat_id = message.chat.id,message_id = message.message_id)
	await bot.send_message(chat_id = admin_chat_id, 
		text =f"""     Web
		message_id: {message.message_id}
		chat_id: {message.chat.id}
		Username {message.from_user.username}
		First_name: {message.from_user.first_name}
		Last_name: {message.from_user.last_name}
		Language: {message.from_user.language_code}
		Id: {message.from_user.id}""")
	await state.clear()

@dp.message(order.web )
async def videorec(message: Message, state: FSMContext):
	b = []
	b.append([InlineKeyboardButton(text = "Cancel", callback_data = "cancel")])
	markup = InlineKeyboardMarkup(inline_keyboard = b)
	await bot.send_message(chat_id = message.chat.id,
		text = "repeat your request or click cancel",
		reply_markup = markup)

@dp.message(order.document ,F.content_type.in_({"text","document"}))
async def videorec(message: Message, state: FSMContext):
	await bot.send_message(chat_id = message.chat.id, text = "Thank you. your recommendation will be reviewed by the administrator and then added")
	await bot.forward_message(chat_id = admin_chat_id , from_chat_id = message.chat.id,message_id = message.message_id)
	await bot.send_message(chat_id = admin_chat_id, 
		text =f"""     Web
		message_id: {message.message_id}
		chat_id: {message.chat.id}
		Username {message.from_user.username}
		First_name: {message.from_user.first_name}
		Last_name: {message.from_user.last_name}
		Language: {message.from_user.language_code}
		Id: {message.from_user.id}""")
	await state.clear()

@dp.message(order.document )
async def videorec(message: Message, state: FSMContext):
	b = []
	b.append([InlineKeyboardButton(text = "Cancel", callback_data = "cancel")])
	markup = InlineKeyboardMarkup(inline_keyboard = b)
	await bot.send_message(chat_id = message.chat.id,
		text = "repeat your request or click cancel",
		reply_markup = markup)



@dp.callback_query(lambda c: c.data == 'cancel')
async def rec(callback_query : types.CallbackQuery,state: FSMContext ):
	state.clear()
	await bot.delete_message(callback_query.message.chat.id,callback_query.message.message_id )

@dp.message(F.content_type == "sticker")
async def kal(message: Message):
	print(message.content_type)
	
	await bot.send_message(chat_id = message.chat.id , text = "working filter")

@dp.message(F.content_type == "text",)
async def message_handler(message: Message):
	print(message.content_type)
	await main_menu(message, message.text)


async def main():
	await dp.start_polling(bot)
if __name__ == '__main__':
	asyncio.run(main())