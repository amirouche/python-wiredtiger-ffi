from wiredtiger_ffi._wiredtiger import ffi
from wiredtiger_ffi._wiredtiger import lib


class WiredtigerException(Exception):
    pass


def charp_or_null(text):
    return text.encode('utf-8') if text else ffi.NULL


def check(code, ret=None):
    if code == 0:
        return ret
    else:
        msg = ffi.string(lib.wiredtiger_strerror(code))
        raise WiredtigerException(msg.decode('utf-8'))


class Wiredtiger:

    def __init__(self, home, config):
        wt = ffi.new('WT_CONNECTION **')
        home, config = map(charp_or_null, (home, config))
        code = lib.wiredtiger_open(home, ffi.NULL, config, wt)
        self._connection = check(code, wt)

    def close(self, config=None):
        config = charp_or_null(config)
        check(self._connection[0].close(self._connection[0], config))

    def home(self):
        home = self._connection[0].get_home(self._connection[0])
        home = ffi.string(home).decode('utf-8')
        return home

    def open_session(self, config=None):
        session = ffi.new('WT_SESSION **')
        config = charp_or_null(config)
        code = self._connection[0].open_session(
            self._connection[0], ffi.NULL,
            config,
            session
        )
        return check(code, Session(session))


class Session:

    def __init__(self, session):
        self._session = session

    def close(self, config=None):
        config = charp_or_null(config)
        check(self._session[0].close(self._session[0], config))

    def open_cursor(self, uri, config=''):
        cursor = ffi.new('WT_CURSOR **')
        uri = charp_or_null(uri)
        config = charp_or_null(config)
        code = self._session[0].open_cursor(
            self._session[0],
            uri,
            ffi.NULL,
            config,
            cursor
        )
        return check(code, Cursor(cursor))

    def create(self, name, config=None):
        name = charp_or_null(name)
        config = charp_or_null(config)
        check(self._session[0].create(self._session[0], name, config))

    def transaction_begin(self, config=None):
        config = charp_or_null(config)
        check(self._session[0].begin_transaction(self._session[0], config))

    def transaction_commit(self, config=None):
        config = charp_or_null(config)
        check(self._session[0].commit_transaction(self._session[0], config))

    def transaction_rollback(self, config=None):
        config = charp_or_null(config)
        check(self._session[0].rollback_transaction(self._session[0], config))


def make_item(x):
    item = ffi.new('WT_ITEM *')
    item[0].data = ffi.new('char[]', x)
    item[0].size = len(x)
    return item


TO_CDATA = {
    'S': lambda x: ffi.new('char[]', x.encode('utf-8')),
    'Q': lambda x: ffi.cast('uint64_t', x),
    'q': lambda x: ffi.cast('int64_t', x),
    'u': make_item
}

INIT_CDATA = {
    'S': lambda: ffi.new('char **'),
    'Q': lambda: ffi.new('uint64_t *'),
    'q': lambda: ffi.new('int64_t *'),
    'u': lambda: ffi.new('WT_ITEM *'),
    'U': lambda: ffi.new('WT_ITEM *'),
}

FROM_CDATA = {
    'S': lambda x: ffi.string(x[0]).decode('utf-8'),
    'Q': lambda x: x[0],
    'q': lambda x: x[0],
    'u': lambda x: ffi.string(ffi.cast('char *', x[0].data), x[0].size),
    'U': lambda x: ffi.string(ffi.cast('char *', x[0].data), x[0].size)
}


class Cursor:

    def __init__(self, cursor):
        self._cursor = cursor
        self.__unset_ptr()

    def _key_format(self):
        return ffi.string(self._cursor[0].key_format).decode('utf-8')

    def _value_format(self):
        return ffi.string(self._cursor[0].value_format).decode('utf-8')

    def get_key(self):
        formats = self._key_format()
        args = list(map(lambda f: INIT_CDATA[f](), formats))
        self.__key_ptr.extend(args)
        args.insert(0, self._cursor[0])
        self._cursor[0].get_key(*args)
        args.pop(0)
        return list(map(lambda f, x: FROM_CDATA[f](x), formats, args))

    def get_value(self):
        formats = self._value_format()
        args = list(map(lambda f: INIT_CDATA[f](), formats))
        self.__key_ptr.extend(args)
        args.insert(0, self._cursor[0])
        self._cursor[0].get_value(*args)
        args.pop(0)
        return list(map(lambda f, x: FROM_CDATA[f](x), formats, args))

    def set_key(self, *key):
        self.__key_ptr = list(key)
        formats = self._key_format()
        args = list(map(lambda f, x: TO_CDATA[f](x), formats, key))
        self.__key_ptr.extend(args)
        args.insert(0, self._cursor[0])
        self._cursor[0].set_key(*args)
        args.pop(0)

    def set_value(self, *value):
        self.__value_ptr = list(value)
        formats = self._value_format()
        args = list(map(lambda f, x: TO_CDATA[f](x), formats, value))
        self.__value_ptr.extend(args)
        args.insert(0, self._cursor[0])
        self._cursor[0].set_value(*args)
        args.pop(0)

    def __unset_ptr(self):
        self.__key_ptr = list()
        self.__value_ptr = list()

    def insert(self):
        error = self._cursor[0].insert(self._cursor[0])
        return error

    def reset(self):
        error = self._cursor[0].reset(self._cursor[0])
        self.__unset_ptr()
        return error

    def next(self):
        return self._cursor[0].next(self._cursor[0])

    def previous(self):
        return self._cursor[0].previous(self._cursor[0])

    def search(self):
        return self._cursor[0].search(self._cursor[0])

    def search_near(self):
        out = ffi.new('int *')
        code = self._cursor[0].search_near(self._cursor[0], out)
        return check(code, out[0])

    def close(self):
        check(self._cursor[0].close(self._cursor[0]))
