import random

from wiredtiger_ffi import Wiredtiger

# init
wiredtiger = Wiredtiger('tmp', 'create')
session = wiredtiger.open_session()
session.create('table:test', "key_format=Q,value_format=QQ")
cursor = session.open_cursor('table:test')

print('key format', cursor._key_format())
print('value format', cursor._value_format())


# insert
for x in range(10**6):
    print('iteration: {}'.format(x))
    a, b, c = (
        random.randint(0, 2**64),
        random.randint(0, 2**64),
        random.randint(0, 2**64),
    )
    cursor.set_key(a)
    cursor.set_value(b, c)
    cursor.insert()
    cursor.reset()

    cursor.set_key(a)
    print('cursor search output: {}'.format(cursor.search()))
    assert cursor.get_key() == [a]
    assert cursor.get_value() == [b, c]

session.close()
wiredtiger.close()
