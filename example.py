from wiredtiger_ffi import Wiredtiger

# init
wiredtiger = Wiredtiger('tmp', 'create')
session = wiredtiger.open_session()
session.create('table:test', "key_format=Q,value_format=QQ")
cursor = session.open_cursor('table:test')

print('key format', cursor._key_format())
print('value format', cursor._value_format())

# insert
cursor.set_key(123)
cursor.set_value(456, 789)
cursor.insert()
print('key is', cursor.get_key())
print('value is', cursor.get_value())
cursor.reset()

# get
print('\n\n* get')
cursor.next()
print('key is', cursor.get_key())
print('value is ', cursor.get_value())

session.close()
wiredtiger.close()
