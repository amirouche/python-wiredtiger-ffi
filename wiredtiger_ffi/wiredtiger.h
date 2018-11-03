struct __wt_async_callback;
typedef struct __wt_async_callback WT_ASYNC_CALLBACK;
struct __wt_async_op; typedef struct __wt_async_op WT_ASYNC_OP;
struct __wt_collator; typedef struct __wt_collator WT_COLLATOR;
struct __wt_compressor; typedef struct __wt_compressor WT_COMPRESSOR;
struct __wt_config_item; typedef struct __wt_config_item WT_CONFIG_ITEM;
struct __wt_config_parser;
typedef struct __wt_config_parser WT_CONFIG_PARSER;
struct __wt_connection; typedef struct __wt_connection WT_CONNECTION;
struct __wt_cursor; typedef struct __wt_cursor WT_CURSOR;
struct __wt_data_source; typedef struct __wt_data_source WT_DATA_SOURCE;
struct __wt_encryptor; typedef struct __wt_encryptor WT_ENCRYPTOR;
struct __wt_event_handler; typedef struct __wt_event_handler WT_EVENT_HANDLER;
struct __wt_extension_api; typedef struct __wt_extension_api WT_EXTENSION_API;
struct __wt_extractor; typedef struct __wt_extractor WT_EXTRACTOR;
struct __wt_file_handle; typedef struct __wt_file_handle WT_FILE_HANDLE;
struct __wt_file_system; typedef struct __wt_file_system WT_FILE_SYSTEM;
struct __wt_item; typedef struct __wt_item WT_ITEM;
struct __wt_modify; typedef struct __wt_modify WT_MODIFY;
struct __wt_session; typedef struct __wt_session WT_SESSION;

struct __wt_item {
  const void *data;
  size_t size;
  void *mem;
  size_t memsize;
  uint32_t flags;
};

struct __wt_modify {
  WT_ITEM data;
  size_t offset;
  size_t size;
};

struct __wt_cursor {
  WT_SESSION *session;
  const char *uri;
  const char *key_format;
  const char *value_format;
  int (*(get_key))(WT_CURSOR *cursor, ...);
  int (*(get_value))(WT_CURSOR *cursor, ...);
  void (*(set_key))(WT_CURSOR *cursor, ...);
  void (*(set_value))(WT_CURSOR *cursor, ...);
  int (*(compare))(WT_CURSOR *cursor, WT_CURSOR *other, int *comparep);
  int (*(equals))(WT_CURSOR *cursor, WT_CURSOR *other, int *equalp);
  int (*(next))(WT_CURSOR *cursor);
  int (*(prev))(WT_CURSOR *cursor);
  int (*(reset))(WT_CURSOR *cursor);
  int (*(search))(WT_CURSOR *cursor);
  int (*(search_near))(WT_CURSOR *cursor, int *exactp);
  int (*(insert))(WT_CURSOR *cursor);
  int (*(modify))(WT_CURSOR *cursor, WT_MODIFY *entries, int nentries);
  int (*(update))(WT_CURSOR *cursor);
  int (*(remove))(WT_CURSOR *cursor);
  int (*(reserve))(WT_CURSOR *cursor);
  int (*(close))(WT_CURSOR *cursor);
  int (*(reconfigure))(WT_CURSOR *cursor, const char *config);

  struct {
    WT_CURSOR *tqe_next;
    WT_CURSOR **tqe_prev;
  } q;

  uint64_t recno;
  uint8_t raw_recno_buf[9];
  void *json_private;
  void *lang_private;
  WT_ITEM key, value;
  int saved_err;
  const char *internal_uri;
  uint32_t flags;
};

typedef enum {
  WT_AOP_NONE=0,
  WT_AOP_COMPACT,
  WT_AOP_INSERT,
  WT_AOP_REMOVE,
  WT_AOP_SEARCH,
  WT_AOP_UPDATE
} WT_ASYNC_OPTYPE;

struct __wt_async_op {
  WT_CONNECTION *connection;
  const char *key_format;
  const char *value_format;
  void *app_private;
  int (*(get_key))(WT_ASYNC_OP *op, ...);
  int (*(get_value))(WT_ASYNC_OP *op, ...);
  void (*(set_key))(WT_ASYNC_OP *op, ...);
  void (*(set_value))(WT_ASYNC_OP *op, ...);
  int (*(search))(WT_ASYNC_OP *op);
  int (*(insert))(WT_ASYNC_OP *op);
  int (*(update))(WT_ASYNC_OP *op);
  int (*(remove))(WT_ASYNC_OP *op);
  int (*(compact))(WT_ASYNC_OP *op);
  uint64_t (*(get_id))(WT_ASYNC_OP *op);
  WT_ASYNC_OPTYPE (*(get_type))(WT_ASYNC_OP *op);
  WT_CURSOR c;
};

struct __wt_session {
  WT_CONNECTION *connection;
  void *app_private;
  int (*(close))(WT_SESSION *session,
                 const char *config);
  int (*(reconfigure))(WT_SESSION *session, const char *config);
  const char *(*(strerror))(WT_SESSION *session, int error);
  int (*(open_cursor))(WT_SESSION *session,
                       const char *uri, WT_CURSOR *to_dup,
                       const char *config, WT_CURSOR **cursorp);
  int (*(alter))(WT_SESSION *session,
                 const char *name, const char *config);
  int (*(create))(WT_SESSION *session,
                  const char *name, const char *config);
  int (*(compact))(WT_SESSION *session,
                   const char *name, const char *config);
  int (*(drop))(WT_SESSION *session,
                const char *name, const char *config);
  int (*(join))(WT_SESSION *session, WT_CURSOR *join_cursor,
                WT_CURSOR *ref_cursor, const char *config);
  int (*(log_flush))(WT_SESSION *session, const char *config);
  int (*(log_printf))(WT_SESSION *session, const char *fmt, ...);
  int (*(rebalance))(
                     WT_SESSION *session, const char *uri, const char *config);
  int (*(rename))(WT_SESSION *session,
                  const char *uri, const char *newuri, const char *config);
  int (*(reset))(WT_SESSION *session);
  int (*(salvage))(WT_SESSION *session,
                   const char *name, const char *config);
  int (*(truncate))(WT_SESSION *session,
                    const char *name,
                    WT_CURSOR *start,
                    WT_CURSOR *stop,
                    const char *config);
  int (*(upgrade))(WT_SESSION *session,
                   const char *name, const char *config);
  int (*(verify))(WT_SESSION *session,
                  const char *name, const char *config);
  int (*(begin_transaction))(WT_SESSION *session, const char *config);
  int (*(commit_transaction))(WT_SESSION *session, const char *config);
  int (*(rollback_transaction))(WT_SESSION *session, const char *config);
  int (*(timestamp_transaction))(WT_SESSION *session, const char *config);
  int (*(checkpoint))(WT_SESSION *session, const char *config);
  int (*(snapshot))(WT_SESSION *session, const char *config);
  int (*(transaction_pinned_range))(WT_SESSION* session, uint64_t *range);
  int (*(transaction_sync))(WT_SESSION *session, const char *config);
};

struct __wt_connection {
  int (*(async_flush))(WT_CONNECTION *connection);
  int (*(async_new_op))(WT_CONNECTION *connection,
                        const char *uri, const char *config, WT_ASYNC_CALLBACK *callback,
                        WT_ASYNC_OP **asyncopp);
  int (*(close))(WT_CONNECTION *connection,
                 const char *config);
  int (*(debug_info))(WT_CONNECTION *connection, const char *config);
  int (*(reconfigure))(WT_CONNECTION *connection, const char *config);
  const char *(*(get_home))(WT_CONNECTION *connection);
  int (*(configure_method))(WT_CONNECTION *connection,
                            const char *method, const char *uri,
                            const char *config, const char *type, const char *check);
  int (*(is_new))(WT_CONNECTION *connection);
  int (*(open_session))(WT_CONNECTION *connection,
                        WT_EVENT_HANDLER *errhandler, const char *config,
                        WT_SESSION **sessionp);
  int (*(query_timestamp))(
                           WT_CONNECTION *connection, char *hex_timestamp, const char *config);
  int (*(set_timestamp))(
                         WT_CONNECTION *connection, const char *config);
  int (*(rollback_to_stable))(
                              WT_CONNECTION *connection, const char *config);
  int (*(load_extension))(WT_CONNECTION *connection,
                          const char *path, const char *config);
  int (*(add_data_source))(WT_CONNECTION *connection, const char *prefix,
                           WT_DATA_SOURCE *data_source, const char *config);
  int (*(add_collator))(WT_CONNECTION *connection,
                        const char *name, WT_COLLATOR *collator, const char *config);
  int (*(add_compressor))(WT_CONNECTION *connection,
                          const char *name, WT_COMPRESSOR *compressor, const char *config);
  int (*(add_encryptor))(WT_CONNECTION *connection,
                         const char *name, WT_ENCRYPTOR *encryptor, const char *config);
  int (*(add_extractor))(WT_CONNECTION *connection, const char *name,
                         WT_EXTRACTOR *extractor, const char *config);
  int (*(set_file_system))(
                           WT_CONNECTION *connection, WT_FILE_SYSTEM *fs, const char *config);
  WT_EXTENSION_API *(*(get_extension_api))(WT_CONNECTION *wt_conn);
};

int wiredtiger_open(const char *home,
                    WT_EVENT_HANDLER *errhandler, const char *config,
                    WT_CONNECTION **connectionp) ;

const char *wiredtiger_strerror(int error) ;

struct __wt_async_callback {
  int (*notify)(WT_ASYNC_CALLBACK *cb, WT_ASYNC_OP *op,
                int op_ret, uint32_t flags);
};

struct __wt_event_handler {
  int (*handle_error)(WT_EVENT_HANDLER *handler,
                      WT_SESSION *session, int error, const char *message);
  int (*handle_message)(WT_EVENT_HANDLER *handler,
                        WT_SESSION *session, const char *message);
  int (*handle_progress)(WT_EVENT_HANDLER *handler,
                         WT_SESSION *session, const char *operation, uint64_t progress);
  int (*handle_close)(WT_EVENT_HANDLER *handler,
                      WT_SESSION *session, WT_CURSOR *cursor);
};

int wiredtiger_struct_pack(WT_SESSION *session,
                           void *buffer, size_t size, const char *format, ...)
  ;

int wiredtiger_struct_size(WT_SESSION *session,
                           size_t *sizep, const char *format, ...) ;

int wiredtiger_struct_unpack(WT_SESSION *session,
                             const void *buffer, size_t size, const char *format, ...)
  ;

typedef struct __wt_pack_stream WT_PACK_STREAM;

int wiredtiger_pack_start(WT_SESSION *session,
                          const char *format, void *buffer, size_t size, WT_PACK_STREAM **psp)
  ;

int wiredtiger_unpack_start(WT_SESSION *session,
                            const char *format, const void *buffer, size_t size, WT_PACK_STREAM **psp)
  ;

int wiredtiger_pack_close(WT_PACK_STREAM *ps, size_t *usedp)
  ;

int wiredtiger_pack_item(WT_PACK_STREAM *ps, WT_ITEM *item)
  ;

int wiredtiger_pack_int(WT_PACK_STREAM *ps, int64_t i)
  ;

int wiredtiger_pack_str(WT_PACK_STREAM *ps, const char *s)
  ;

int wiredtiger_pack_uint(WT_PACK_STREAM *ps, uint64_t u)
  ;

int wiredtiger_unpack_item(WT_PACK_STREAM *ps, WT_ITEM *item)
  ;

int wiredtiger_unpack_int(WT_PACK_STREAM *ps, int64_t *ip)
  ;

int wiredtiger_unpack_str(WT_PACK_STREAM *ps, const char **sp)
  ;

int wiredtiger_unpack_uint(WT_PACK_STREAM *ps, uint64_t *up)
  ;

struct __wt_config_item {
  const char *str;
  size_t len;
  int64_t val;
  enum {
    WT_CONFIG_ITEM_STRING,
    WT_CONFIG_ITEM_BOOL,
    WT_CONFIG_ITEM_ID,
    WT_CONFIG_ITEM_NUM,
    WT_CONFIG_ITEM_STRUCT
  }
    type;
};

int wiredtiger_config_validate(WT_SESSION *session,
                               WT_EVENT_HANDLER *errhandler, const char *name, const char *config)
  ;

int wiredtiger_config_parser_open(WT_SESSION *session,
                                  const char *config, size_t len, WT_CONFIG_PARSER **config_parserp)
  ;

struct __wt_config_parser {
  int (*(close))(WT_CONFIG_PARSER *config_parser);
  int (*(next))(WT_CONFIG_PARSER *config_parser,
                WT_CONFIG_ITEM *key, WT_CONFIG_ITEM *value);
  int (*(get))(WT_CONFIG_PARSER *config_parser,
               const char *key, WT_CONFIG_ITEM *value);
};

const char *wiredtiger_version(int *majorp, int *minorp, int *patchp)
  ;

struct __wt_config_arg; typedef struct __wt_config_arg WT_CONFIG_ARG;

struct __wt_collator {
  int (*compare)(WT_COLLATOR *collator, WT_SESSION *session,
                 const WT_ITEM *key1, const WT_ITEM *key2, int *cmp);
  int (*customize)(WT_COLLATOR *collator, WT_SESSION *session,
                   const char *uri, WT_CONFIG_ITEM *passcfg, WT_COLLATOR **customp);
  int (*terminate)(WT_COLLATOR *collator, WT_SESSION *session);
};
