struct __wt_async_callback;
	typedef struct __wt_async_callback WT_ASYNC_CALLBACK;
struct __wt_async_op;	    typedef struct __wt_async_op WT_ASYNC_OP;
struct __wt_collator;	    typedef struct __wt_collator WT_COLLATOR;
struct __wt_compressor;	    typedef struct __wt_compressor WT_COMPRESSOR;
struct __wt_config_item;    typedef struct __wt_config_item WT_CONFIG_ITEM;
struct __wt_config_parser;
	typedef struct __wt_config_parser WT_CONFIG_PARSER;
struct __wt_connection;	    typedef struct __wt_connection WT_CONNECTION;
struct __wt_cursor;	    typedef struct __wt_cursor WT_CURSOR;
struct __wt_data_source;    typedef struct __wt_data_source WT_DATA_SOURCE;
struct __wt_encryptor;	    typedef struct __wt_encryptor WT_ENCRYPTOR;
struct __wt_event_handler;  typedef struct __wt_event_handler WT_EVENT_HANDLER;
struct __wt_extension_api;  typedef struct __wt_extension_api WT_EXTENSION_API;
struct __wt_extractor;	    typedef struct __wt_extractor WT_EXTRACTOR;
struct __wt_item;	    typedef struct __wt_item WT_ITEM;
struct __wt_lsn;	    typedef struct __wt_lsn WT_LSN;
struct __wt_session;	    typedef struct __wt_session WT_SESSION;


/*!
 * Open a connection to a database.
 *
 * @snippet ex_all.c Open a connection
 *
 * @param home The path to the database home directory.  See @ref home
 * for more information.
 * @param errhandler An error handler.  If <code>NULL</code>, a builtin error
 * handler is installed that writes error messages to stderr
 * @configstart{wiredtiger_open, see dist/api_data.py}
 * @config{async = (, asynchronous operations configuration options., a set of
 * related configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;enabled, enable asynchronous operation., a
 * boolean flag; default \c false.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;ops_max,
 * maximum number of expected simultaneous asynchronous operations., an integer
 * between 1 and 4096; default \c 1024.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;threads, the number of worker threads to
 * service asynchronous requests.  Each worker thread uses a session from the
 * configured session_max., an integer between 1 and 20; default \c 2.}
 * @config{
 * ),,}
 * @config{buffer_alignment, in-memory alignment (in bytes) for buffers used for
 * I/O. The default value of -1 indicates a platform-specific alignment value
 * should be used (4KB on Linux systems when direct I/O is configured\, zero
 * elsewhere)., an integer between -1 and 1MB; default \c -1.}
 * @config{cache_overhead, assume the heap allocator overhead is the specified
 * percentage\, and adjust the cache usage by that amount (for example\, if
 * there is 10GB of data in cache\, a percentage of 10 means WiredTiger treats
 * this as 11GB). This value is configurable because different heap allocators
 * have different overhead and different workloads will have different heap
 * allocation sizes and patterns\, therefore applications may need to adjust
 * this value based on allocator choice and behavior in measured workloads., an
 * integer between 0 and 30; default \c 8.}
 * @config{cache_size, maximum heap memory to allocate for the cache.  A
 * database should configure either \c cache_size or \c shared_cache but not
 * both., an integer between 1MB and 10TB; default \c 100MB.}
 * @config{checkpoint = (, periodically checkpoint the database.  Enabling the
 * checkpoint server uses a session from the configured session_max., a set of
 * related configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;log_size, wait for this amount of log record
 * bytes to be written to the log between each checkpoint.  A database can
 * configure both log_size and wait to set an upper bound for checkpoints;
 * setting this value above 0 configures periodic checkpoints., an integer
 * between 0 and 2GB; default \c 0.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;name, the
 * checkpoint name., a string; default \c "WiredTigerCheckpoint".}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;wait, seconds to wait between each
 * checkpoint; setting this value above 0 configures periodic checkpoints., an
 * integer between 0 and 100000; default \c 0.}
 * @config{ ),,}
 * @config{checkpoint_sync, flush files to stable storage when closing or
 * writing checkpoints., a boolean flag; default \c true.}
 * @config{config_base, write the base configuration file if creating the
 * database\, see @ref config_base for more information., a boolean flag;
 * default \c true.}
 * @config{create, create the database if it does not exist., a boolean flag;
 * default \c false.}
 * @config{direct_io, Use \c O_DIRECT to access files.  Options are given as a
 * list\, such as <code>"direct_io=[data]"</code>. Configuring \c direct_io
 * requires care\, see @ref tuning_system_buffer_cache_direct_io for important
 * warnings.  Including \c "data" will cause WiredTiger data files to use \c
 * O_DIRECT\, including \c "log" will cause WiredTiger log files to use \c
 * O_DIRECT\, and including \c "checkpoint" will cause WiredTiger data files
 * opened at a checkpoint (i.e: read only) to use \c O_DIRECT., a list\, with
 * values chosen from the following options: \c "checkpoint"\, \c "data"\, \c
 * "log"; default empty.}
 * @config{encryption = (, configure an encryptor for system wide metadata and
 * logs.  If a system wide encryptor is set\, it is also used for encrypting
 * data files and tables\, unless encryption configuration is explicitly set for
 * them when they are created with WT_SESSION::create., a set of related
 * configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;keyid,
 * An identifier that identifies a unique instance of the encryptor.  It is
 * stored in clear text\, and thus is available when the wiredtiger database is
 * reopened.  On the first use of a (name\, keyid) combination\, the
 * WT_ENCRYPTOR::customize function is called with the keyid as an argument., a
 * string; default empty.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;name, Permitted
 * values are \c "none" or custom encryption engine name created with
 * WT_CONNECTION::add_encryptor.  See @ref encryption for more information., a
 * string; default \c none.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;secretkey, A string
 * that is passed to the WT_ENCRYPTOR::customize function.  It is never stored
 * in clear text\, so must be given to any subsequent ::wiredtiger_open calls to
 * reopen the database.  It must also be provided to any "wt" commands used with
 * this database., a string; default empty.}
 * @config{ ),,}
 * @config{error_prefix, prefix string for error messages., a string; default
 * empty.}
 * @config{eviction = (, eviction configuration options., a set of related
 * configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;threads_max, maximum number of threads
 * WiredTiger will start to help evict pages from cache.  The number of threads
 * started will vary depending on the current eviction load.  Each eviction
 * worker thread uses a session from the configured session_max., an integer
 * between 1 and 20; default \c 1.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;threads_min,
 * minimum number of threads WiredTiger will start to help evict pages from
 * cache.  The number of threads currently running will vary depending on the
 * current eviction load., an integer between 1 and 20; default \c 1.}
 * @config{
 * ),,}
 * @config{eviction_dirty_target, continue evicting until the cache has less
 * dirty memory than the value\, as a percentage of the total cache size.  Dirty
 * pages will only be evicted if the cache is full enough to trigger eviction.,
 * an integer between 5 and 99; default \c 80.}
 * @config{eviction_dirty_trigger, trigger eviction when the cache is using this
 * much memory for dirty content\, as a percentage of the total cache size.
 * This setting only alters behavior if it is lower than eviction_trigger., an
 * integer between 5 and 99; default \c 95.}
 * @config{eviction_target, continue evicting until the cache has less total
 * memory than the value\, as a percentage of the total cache size.  Must be
 * less than \c eviction_trigger., an integer between 10 and 99; default \c 80.}
 * @config{eviction_trigger, trigger eviction when the cache is using this much
 * memory\, as a percentage of the total cache size., an integer between 10 and
 * 99; default \c 95.}
 * @config{exclusive, fail if the database already exists\, generally used with
 * the \c create option., a boolean flag; default \c false.}
 * @config{extensions, list of shared library extensions to load (using dlopen).
 * Any values specified to an library extension are passed to
 * WT_CONNECTION::load_extension as the \c config parameter (for example\,
 * <code>extensions=(/path/ext.so={entry=my_entry})</code>)., a list of strings;
 * default empty.}
 * @config{file_extend, file extension configuration.  If set\, extend files of
 * the set type in allocations of the set size\, instead of a block at a time as
 * each new block is written.  For example\,
 * <code>file_extend=(data=16MB)</code>., a list\, with values chosen from the
 * following options: \c "data"\, \c "log"; default empty.}
 * @config{file_manager = (, control how file handles are managed., a set of
 * related configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;close_handle_minimum, number of handles open
 * before the file manager will look for handles to close., an integer greater
 * than or equal to 0; default \c 250.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;close_idle_time, amount of time in seconds a
 * file handle needs to be idle before attempting to close it.  A setting of 0
 * means that idle handles are not closed., an integer between 0 and 100000;
 * default \c 30.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;close_scan_interval, interval
 * in seconds at which to check for files that are inactive and close them., an
 * integer between 1 and 100000; default \c 10.}
 * @config{ ),,}
 * @config{hazard_max, maximum number of simultaneous hazard pointers per
 * session handle., an integer greater than or equal to 15; default \c 1000.}
 * @config{log = (, enable logging.  Enabling logging uses three sessions from
 * the configured session_max., a set of related configuration options defined
 * below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;archive, automatically archive
 * unneeded log files., a boolean flag; default \c true.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;compressor, configure a compressor for log
 * records.  Permitted values are \c "none" or custom compression engine name
 * created with WT_CONNECTION::add_compressor.  If WiredTiger has builtin
 * support for \c "bzip2"\, \c "snappy"\, \c "lz4" or \c "zlib" compression\,
 * these names are also available.  See @ref compression for more information.,
 * a string; default \c none.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;enabled, enable
 * logging subsystem., a boolean flag; default \c false.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;file_max, the maximum size of log files., an
 * integer between 100KB and 2GB; default \c 100MB.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;path, the path to a directory into which the
 * log files are written.  If the value is not an absolute path name\, the files
 * are created relative to the database home., a string; default empty.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;prealloc, pre-allocate log files., a boolean
 * flag; default \c true.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;recover, run recovery
 * or error if recovery needs to run after an unclean shutdown., a string\,
 * chosen from the following options: \c "error"\, \c "on"; default \c on.}
 * @config{ ),,}
 * @config{lsm_manager = (, configure database wide options for LSM tree
 * management.  The LSM manager is started automatically the first time an LSM
 * tree is opened.  The LSM manager uses a session from the configured
 * session_max., a set of related configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;merge, merge LSM chunks where possible., a
 * boolean flag; default \c true.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;worker_thread_max, Configure a set of threads
 * to manage merging LSM trees in the database.  Each worker thread uses a
 * session handle from the configured session_max., an integer between 3 and 20;
 * default \c 4.}
 * @config{ ),,}
 * @config{mmap, Use memory mapping to access files when possible., a boolean
 * flag; default \c true.}
 * @config{multiprocess, permit sharing between processes (will automatically
 * start an RPC server for primary processes and use RPC for secondary
 * processes). <b>Not yet supported in WiredTiger</b>., a boolean flag; default
 * \c false.}
 * @config{session_max, maximum expected number of sessions (including server
 * threads)., an integer greater than or equal to 1; default \c 100.}
 * @config{shared_cache = (, shared cache configuration options.  A database
 * should configure either a cache_size or a shared_cache not both.  Enabling a
 * shared cache uses a session from the configured session_max., a set of
 * related configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;chunk, the granularity that a shared cache is
 * redistributed., an integer between 1MB and 10TB; default \c 10MB.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;name, the name of a cache that is shared
 * between databases or \c "none" when no shared cache is configured., a string;
 * default \c none.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;reserve, amount of cache
 * this database is guaranteed to have available from the shared cache.  This
 * setting is per database.  Defaults to the chunk size., an integer; default \c
 * 0.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;size, maximum memory to allocate for the
 * shared cache.  Setting this will update the value if one is already set., an
 * integer between 1MB and 10TB; default \c 500MB.}
 * @config{ ),,}
 * @config{statistics, Maintain database statistics\, which may impact
 * performance.  Choosing "all" maintains all statistics regardless of cost\,
 * "fast" maintains a subset of statistics that are relatively inexpensive\,
 * "none" turns off all statistics.  The "clear" configuration resets statistics
 * after they are gathered\, where appropriate (for example\, a cache size
 * statistic is not cleared\, while the count of cursor insert operations will
 * be cleared). When "clear" is configured for the database\, gathered
 * statistics are reset each time a statistics cursor is used to gather
 * statistics\, as well as each time statistics are logged using the \c
 * statistics_log configuration.  See @ref statistics for more information., a
 * list\, with values chosen from the following options: \c "all"\, \c "fast"\,
 * \c "none"\, \c "clear"; default \c none.}
 * @config{statistics_log = (, log any statistics the database is configured to
 * maintain\, to a file.  See @ref statistics for more information.  Enabling
 * the statistics log server uses a session from the configured session_max., a
 * set of related configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;on_close, log statistics on database close.,
 * a boolean flag; default \c false.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;path, the
 * pathname to a file into which the log records are written\, may contain ISO C
 * standard strftime conversion specifications.  If the value is not an absolute
 * path name\, the file is created relative to the database home., a string;
 * default \c "WiredTigerStat.%d.%H".}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;sources,
 * if non-empty\, include statistics for the list of data source URIs\, if they
 * are open at the time of the statistics logging.  The list may include URIs
 * matching a single data source ("table:mytable")\, or a URI matching all data
 * sources of a particular type ("table:")., a list of strings; default empty.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;timestamp, a timestamp prepended to each log
 * record\, may contain strftime conversion specifications., a string; default
 * \c "%b %d %H:%M:%S".}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;wait, seconds to wait
 * between each write of the log records; setting this value above 0 configures
 * statistics logging., an integer between 0 and 100000; default \c 0.}
 * @config{
 * ),,}
 * @config{transaction_sync = (, how to sync log records when the transaction
 * commits., a set of related configuration options defined below.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;enabled, whether to sync the log on every
 * commit by default\, can be overridden by the \c sync setting to
 * WT_SESSION::commit_transaction., a boolean flag; default \c false.}
 * @config{&nbsp;&nbsp;&nbsp;&nbsp;method, the method used to ensure log records
 * are stable on disk\, see @ref tune_durability for more information., a
 * string\, chosen from the following options: \c "dsync"\, \c "fsync"\, \c
 * "none"; default \c fsync.}
 * @config{ ),,}
 * @config{use_environment_priv, use the \c WIREDTIGER_CONFIG and \c
 * WIREDTIGER_HOME environment variables regardless of whether or not the
 * process is running with special privileges.  See @ref home for more
 * information., a boolean flag; default \c false.}
 * @config{verbose, enable messages for various events.  Only available if
 * WiredTiger is configured with --enable-verbose.  Options are given as a
 * list\, such as <code>"verbose=[evictserver\,read]"</code>., a list\, with
 * values chosen from the following options: \c "api"\, \c "block"\, \c
 * "checkpoint"\, \c "compact"\, \c "evict"\, \c "evictserver"\, \c "fileops"\,
 * \c "log"\, \c "lsm"\, \c "lsm_manager"\, \c "metadata"\, \c "mutex"\, \c
 * "overflow"\, \c "read"\, \c "reconcile"\, \c "recovery"\, \c "salvage"\, \c
 * "shared_cache"\, \c "split"\, \c "temporary"\, \c "transaction"\, \c
 * "verify"\, \c "version"\, \c "write"; default empty.}
 * @configend
 * Additionally, if files named \c WiredTiger.config or \c WiredTiger.basecfg
 * appear in the WiredTiger home directory, they are read for configuration
 * values (see @ref config_file and @ref config_base for details).
 * See @ref config_order for ordering of the configuration mechanisms.
 * @param[out] connectionp A pointer to the newly opened connection handle
 * @errors
 */
int wiredtiger_open(const char *home,
    WT_EVENT_HANDLER *errhandler, const char *config,
    WT_CONNECTION **connectionp);

const char *wiredtiger_strerror(int error);


struct __wt_connection {
	/*!
	 * @name Async operation handles
	 * @{
	 */
	/*!
	 * Wait for all outstanding operations to complete.
	 *
	 * @snippet ex_async.c async flush
	 *
	 * @param connection the connection handle
	 * @errors
	 */
	int (*async_flush)(WT_CONNECTION *connection);

	/*!
	 * Return an async operation handle
	 *
	 * @snippet ex_async.c async handle allocation
	 *
	 * @param connection the connection handle
	 * @param uri the connection handle
	 * @configstart{WT_CONNECTION.async_new_op, see dist/api_data.py}
	 * @config{append, append the value as a new record\, creating a new
	 * record number key; valid only for operations with record number
	 * keys., a boolean flag; default \c false.}
	 * @config{overwrite, configures whether the cursor's insert\, update
	 * and remove methods check the existing state of the record.  If \c
	 * overwrite is \c false\, WT_CURSOR::insert fails with
	 * ::WT_DUPLICATE_KEY if the record exists\, WT_CURSOR::update and
	 * WT_CURSOR::remove fail with ::WT_NOTFOUND if the record does not
	 * exist., a boolean flag; default \c true.}
	 * @config{raw, ignore the encodings for the key and value\, manage data
	 * as if the formats were \c "u". See @ref cursor_raw for details., a
	 * boolean flag; default \c false.}
	 * @config{timeout, maximum amount of time to allow for compact in
	 * seconds.  The actual amount of time spent in compact may exceed the
	 * configured value.  A value of zero disables the timeout., an integer;
	 * default \c 1200.}
	 * @configend
	 * @param callback the operation callback
	 * @param[out] asyncopp the new op handle
	 * @errors
	 * If there are no available handles, \c EBUSY is returned.
	 */
	int (*async_new_op)(WT_CONNECTION *connection,
	    const char *uri, const char *config, WT_ASYNC_CALLBACK *callback,
	    WT_ASYNC_OP **asyncopp);
	/*! @} */

	/*!
	 * Close a connection.
	 *
	 * Any open sessions will be closed.
	 *
	 * @snippet ex_all.c Close a connection
	 *
	 * @param connection the connection handle
	 * @configstart{WT_CONNECTION.close, see dist/api_data.py}
	 * @config{leak_memory, don't free memory during close., a boolean flag;
	 * default \c false.}
	 * @configend
	 * @errors
	 */
	int (*close)(WT_CONNECTION *connection,
	    const char *config);

	/*!
	 * Reconfigure a connection handle.
	 *
	 * @snippet ex_all.c Reconfigure a connection
	 *
	 * @param connection the connection handle
	 * @configstart{WT_CONNECTION.reconfigure, see dist/api_data.py}
	 * @config{async = (, asynchronous operations configuration options., a
	 * set of related configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;enabled, enable asynchronous
	 * operation., a boolean flag; default \c false.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;ops_max, maximum number of expected
	 * simultaneous asynchronous operations., an integer between 1 and 4096;
	 * default \c 1024.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;threads, the number
	 * of worker threads to service asynchronous requests.  Each worker
	 * thread uses a session from the configured session_max., an integer
	 * between 1 and 20; default \c 2.}
	 * @config{ ),,}
	 * @config{cache_overhead, assume the heap allocator overhead is the
	 * specified percentage\, and adjust the cache usage by that amount (for
	 * example\, if there is 10GB of data in cache\, a percentage of 10
	 * means WiredTiger treats this as 11GB). This value is configurable
	 * because different heap allocators have different overhead and
	 * different workloads will have different heap allocation sizes and
	 * patterns\, therefore applications may need to adjust this value based
	 * on allocator choice and behavior in measured workloads., an integer
	 * between 0 and 30; default \c 8.}
	 * @config{cache_size, maximum heap memory to allocate for the cache.  A
	 * database should configure either \c cache_size or \c shared_cache but
	 * not both., an integer between 1MB and 10TB; default \c 100MB.}
	 * @config{checkpoint = (, periodically checkpoint the database.
	 * Enabling the checkpoint server uses a session from the configured
	 * session_max., a set of related configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;log_size, wait for this amount of log
	 * record bytes to be written to the log between each checkpoint.  A
	 * database can configure both log_size and wait to set an upper bound
	 * for checkpoints; setting this value above 0 configures periodic
	 * checkpoints., an integer between 0 and 2GB; default \c 0.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;name, the checkpoint name., a string;
	 * default \c "WiredTigerCheckpoint".}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;wait, seconds to wait between each
	 * checkpoint; setting this value above 0 configures periodic
	 * checkpoints., an integer between 0 and 100000; default \c 0.}
	 * @config{ ),,}
	 * @config{error_prefix, prefix string for error messages., a string;
	 * default empty.}
	 * @config{eviction = (, eviction configuration options., a set of
	 * related configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;threads_max, maximum number of
	 * threads WiredTiger will start to help evict pages from cache.  The
	 * number of threads started will vary depending on the current eviction
	 * load.  Each eviction worker thread uses a session from the configured
	 * session_max., an integer between 1 and 20; default \c 1.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;threads_min, minimum number of
	 * threads WiredTiger will start to help evict pages from cache.  The
	 * number of threads currently running will vary depending on the
	 * current eviction load., an integer between 1 and 20; default \c 1.}
	 * @config{ ),,}
	 * @config{eviction_dirty_target, continue evicting until the cache has
	 * less dirty memory than the value\, as a percentage of the total cache
	 * size.  Dirty pages will only be evicted if the cache is full enough
	 * to trigger eviction., an integer between 5 and 99; default \c 80.}
	 * @config{eviction_dirty_trigger, trigger eviction when the cache is
	 * using this much memory for dirty content\, as a percentage of the
	 * total cache size.  This setting only alters behavior if it is lower
	 * than eviction_trigger., an integer between 5 and 99; default \c 95.}
	 * @config{eviction_target, continue evicting until the cache has less
	 * total memory than the value\, as a percentage of the total cache
	 * size.  Must be less than \c eviction_trigger., an integer between 10
	 * and 99; default \c 80.}
	 * @config{eviction_trigger, trigger eviction when the cache is using
	 * this much memory\, as a percentage of the total cache size., an
	 * integer between 10 and 99; default \c 95.}
	 * @config{file_manager = (, control how file handles are managed., a
	 * set of related configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;close_handle_minimum, number of
	 * handles open before the file manager will look for handles to close.,
	 * an integer greater than or equal to 0; default \c 250.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;close_idle_time, amount of time in
	 * seconds a file handle needs to be idle before attempting to close it.
	 * A setting of 0 means that idle handles are not closed., an integer
	 * between 0 and 100000; default \c 30.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;close_scan_interval, interval in
	 * seconds at which to check for files that are inactive and close
	 * them., an integer between 1 and 100000; default \c 10.}
	 * @config{ ),,}
	 * @config{lsm_manager = (, configure database wide options for LSM tree
	 * management.  The LSM manager is started automatically the first time
	 * an LSM tree is opened.  The LSM manager uses a session from the
	 * configured session_max., a set of related configuration options
	 * defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;merge, merge LSM
	 * chunks where possible., a boolean flag; default \c true.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;worker_thread_max, Configure a set of
	 * threads to manage merging LSM trees in the database.  Each worker
	 * thread uses a session handle from the configured session_max., an
	 * integer between 3 and 20; default \c 4.}
	 * @config{ ),,}
	 * @config{shared_cache = (, shared cache configuration options.  A
	 * database should configure either a cache_size or a shared_cache not
	 * both.  Enabling a shared cache uses a session from the configured
	 * session_max., a set of related configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;chunk, the granularity that a shared
	 * cache is redistributed., an integer between 1MB and 10TB; default \c
	 * 10MB.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;name, the name of a cache that
	 * is shared between databases or \c "none" when no shared cache is
	 * configured., a string; default \c none.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;reserve, amount of cache this
	 * database is guaranteed to have available from the shared cache.  This
	 * setting is per database.  Defaults to the chunk size., an integer;
	 * default \c 0.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;size, maximum memory
	 * to allocate for the shared cache.  Setting this will update the value
	 * if one is already set., an integer between 1MB and 10TB; default \c
	 * 500MB.}
	 * @config{ ),,}
	 * @config{statistics, Maintain database statistics\, which may impact
	 * performance.  Choosing "all" maintains all statistics regardless of
	 * cost\, "fast" maintains a subset of statistics that are relatively
	 * inexpensive\, "none" turns off all statistics.  The "clear"
	 * configuration resets statistics after they are gathered\, where
	 * appropriate (for example\, a cache size statistic is not cleared\,
	 * while the count of cursor insert operations will be cleared). When
	 * "clear" is configured for the database\, gathered statistics are
	 * reset each time a statistics cursor is used to gather statistics\, as
	 * well as each time statistics are logged using the \c statistics_log
	 * configuration.  See @ref statistics for more information., a list\,
	 * with values chosen from the following options: \c "all"\, \c "fast"\,
	 * \c "none"\, \c "clear"; default \c none.}
	 * @config{statistics_log = (, log any statistics the database is
	 * configured to maintain\, to a file.  See @ref statistics for more
	 * information.  Enabling the statistics log server uses a session from
	 * the configured session_max., a set of related configuration options
	 * defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;on_close, log
	 * statistics on database close., a boolean flag; default \c false.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;path, the pathname to a file into
	 * which the log records are written\, may contain ISO C standard
	 * strftime conversion specifications.  If the value is not an absolute
	 * path name\, the file is created relative to the database home., a
	 * string; default \c "WiredTigerStat.%d.%H".}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;sources, if non-empty\, include
	 * statistics for the list of data source URIs\, if they are open at the
	 * time of the statistics logging.  The list may include URIs matching a
	 * single data source ("table:mytable")\, or a URI matching all data
	 * sources of a particular type ("table:")., a list of strings; default
	 * empty.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;timestamp, a timestamp
	 * prepended to each log record\, may contain strftime conversion
	 * specifications., a string; default \c "%b %d %H:%M:%S".}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;wait, seconds to wait between each
	 * write of the log records; setting this value above 0 configures
	 * statistics logging., an integer between 0 and 100000; default \c 0.}
	 * @config{ ),,}
	 * @config{verbose, enable messages for various events.  Only available
	 * if WiredTiger is configured with --enable-verbose.  Options are given
	 * as a list\, such as <code>"verbose=[evictserver\,read]"</code>., a
	 * list\, with values chosen from the following options: \c "api"\, \c
	 * "block"\, \c "checkpoint"\, \c "compact"\, \c "evict"\, \c
	 * "evictserver"\, \c "fileops"\, \c "log"\, \c "lsm"\, \c
	 * "lsm_manager"\, \c "metadata"\, \c "mutex"\, \c "overflow"\, \c
	 * "read"\, \c "reconcile"\, \c "recovery"\, \c "salvage"\, \c
	 * "shared_cache"\, \c "split"\, \c "temporary"\, \c "transaction"\, \c
	 * "verify"\, \c "version"\, \c "write"; default empty.}
	 * @configend
	 * @errors
	 */
	int (*reconfigure)(WT_CONNECTION *connection, const char *config);

	/*!
	 * The home directory of the connection.
	 *
	 * @snippet ex_all.c Get the database home directory
	 *
	 * @param connection the connection handle
	 * @returns a pointer to a string naming the home directory
	 */
	const char *(*get_home)(WT_CONNECTION *connection);

	/*!
	 * Add configuration options for a method.  See
	 * @ref custom_ds_config_add for more information.
	 *
	 * @snippet ex_all.c Configure method configuration
	 *
	 * @param connection the connection handle
	 * @param method the method being configured
	 * @param uri the object type or NULL for all object types
	 * @param config the additional configuration's name and default value
	 * @param type the additional configuration's type (must be one of
	 * \c "boolean"\, \c "int", \c "list" or \c "string")
	 * @param check the additional configuration check string, or NULL if
	 * none
	 * @errors
	 */
	int (*configure_method)(WT_CONNECTION *connection,
	    const char *method, const char *uri,
	    const char *config, const char *type, const char *check);

	/*!
	 * Return if opening this handle created the database.
	 *
	 * @snippet ex_all.c Check if the database is newly created
	 *
	 * @param connection the connection handle
	 * @returns false (zero) if the connection existed before the call to
	 * ::wiredtiger_open, true (non-zero) if it was created by opening this
	 * handle.
	 */
	int (*is_new)(WT_CONNECTION *connection);

	/*!
	 * @name Session handles
	 * @{
	 */
	/*!
	 * Open a session.
	 *
	 * @snippet ex_all.c Open a session
	 *
	 * @param connection the connection handle
	 * @param errhandler An error handler.  If <code>NULL</code>, the
	 * connection's error handler is used
	 * @configstart{WT_CONNECTION.open_session, see dist/api_data.py}
	 * @config{isolation, the default isolation level for operations in this
	 * session., a string\, chosen from the following options: \c
	 * "read-uncommitted"\, \c "read-committed"\, \c "snapshot"; default \c
	 * read-committed.}
	 * @configend
	 * @param[out] sessionp the new session handle
	 * @errors
	 */
	int (*open_session)(WT_CONNECTION *connection,
	    WT_EVENT_HANDLER *errhandler, const char *config,
	    WT_SESSION **sessionp);
	/*! @} */

	/*!
	 * @name Extensions
	 * @{
	 */
	/*!
	 * Load an extension.
	 *
	 * @snippet ex_all.c Load an extension
	 *
	 * @param connection the connection handle
	 * @param path the filename of the extension module, or \c "local" to
	 * search the current application binary for the initialization
	 * function, see @ref extensions for more details.
	 * @configstart{WT_CONNECTION.load_extension, see dist/api_data.py}
	 * @config{config, configuration string passed to the entry point of the
	 * extension as its WT_CONFIG_ARG argument., a string; default empty.}
	 * @config{entry, the entry point of the extension\, called to
	 * initialize the extension when it is loaded.  The signature of the
	 * function must match ::wiredtiger_extension_init., a string; default
	 * \c wiredtiger_extension_init.}
	 * @config{terminate, an optional function in the extension that is
	 * called before the extension is unloaded during WT_CONNECTION::close.
	 * The signature of the function must match
	 * ::wiredtiger_extension_terminate., a string; default \c
	 * wiredtiger_extension_terminate.}
	 * @configend
	 * @errors
	 */
	int (*load_extension)(WT_CONNECTION *connection,
	    const char *path, const char *config);

	/*!
	 * Add a custom data source.  See @ref custom_data_sources for more
	 * information.
	 *
	 * The application must first implement the WT_DATA_SOURCE interface
	 * and then register the implementation with WiredTiger:
	 *
	 * @snippet ex_data_source.c WT_DATA_SOURCE register
	 *
	 * @param connection the connection handle
	 * @param prefix the URI prefix for this data source, e.g., "file:"
	 * @param data_source the application-supplied implementation of
	 *	WT_DATA_SOURCE to manage this data source.
	 * @configempty{WT_CONNECTION.add_data_source, see dist/api_data.py}
	 * @errors
	 */
	int (*add_data_source)(WT_CONNECTION *connection, const char *prefix,
	    WT_DATA_SOURCE *data_source, const char *config);

	/*!
	 * Add a custom collation function.
	 *
	 * The application must first implement the WT_COLLATOR interface and
	 * then register the implementation with WiredTiger:
	 *
	 * @snippet ex_all.c WT_COLLATOR register
	 *
	 * @param connection the connection handle
	 * @param name the name of the collation to be used in calls to
	 * 	WT_SESSION::create, may not be \c "none"
	 * @param collator the application-supplied collation handler
	 * @configempty{WT_CONNECTION.add_collator, see dist/api_data.py}
	 * @errors
	 */
	int (*add_collator)(WT_CONNECTION *connection,
	    const char *name, WT_COLLATOR *collator, const char *config);

	/*!
	 * Add a compression function.
	 *
	 * The application must first implement the WT_COMPRESSOR interface
	 * and then register the implementation with WiredTiger:
	 *
	 * @snippet nop_compress.c WT_COMPRESSOR initialization structure
	 *
	 * @snippet nop_compress.c WT_COMPRESSOR initialization function
	 *
	 * @param connection the connection handle
	 * @param name the name of the compression function to be used in calls
	 *	to WT_SESSION::create, may not be \c "none"
	 * @param compressor the application-supplied compression handler
	 * @configempty{WT_CONNECTION.add_compressor, see dist/api_data.py}
	 * @errors
	 */
	int (*add_compressor)(WT_CONNECTION *connection,
	    const char *name, WT_COMPRESSOR *compressor, const char *config);

	/*!
	 * Add an encryption function.
	 *
	 * The application must first implement the WT_ENCRYPTOR interface
	 * and then register the implementation with WiredTiger:
	 *
	 * @snippet nop_encrypt.c WT_ENCRYPTOR initialization structure
	 *
	 * @snippet nop_encrypt.c WT_ENCRYPTOR initialization function
	 *
	 * @param connection the connection handle
	 * @param name the name of the encryption function to be used in calls
	 *	to WT_SESSION::create, may not be \c "none"
	 * @param encryptor the application-supplied encryption handler
	 * @configempty{WT_CONNECTION.add_encryptor, see dist/api_data.py}
	 * @errors
	 */
	int (*add_encryptor)(WT_CONNECTION *connection,
	    const char *name, WT_ENCRYPTOR *encryptor, const char *config);

	/*!
	 * Add a custom extractor for index keys or column groups.
	 *
	 * The application must first implement the WT_EXTRACTOR interface and
	 * then register the implementation with WiredTiger:
	 *
	 * @snippet ex_all.c WT_EXTRACTOR register
	 *
	 * @param connection the connection handle
	 * @param name the name of the extractor to be used in calls to
	 * 	WT_SESSION::create, may not be \c "none"
	 * @param extractor the application-supplied extractor
	 * @configempty{WT_CONNECTION.add_extractor, see dist/api_data.py}
	 * @errors
	 */
	int (*add_extractor)(WT_CONNECTION *connection, const char *name,
	    WT_EXTRACTOR *extractor, const char *config);

	/*!
	 * Return a reference to the WiredTiger extension functions.
	 *
	 * @snippet ex_data_source.c WT_EXTENSION_API declaration
	 *
	 * @param wt_conn the WT_CONNECTION handle
	 * @returns a reference to a WT_EXTENSION_API structure.
	 */
	WT_EXTENSION_API *(*get_extension_api)(WT_CONNECTION *wt_conn);
	/*! @} */
};


struct __wt_session {
	/*! The connection for this session. */
	WT_CONNECTION *connection;

	/*
	 * Don't expose app_private to non-C language bindings - they have
	 * their own way to attach data to an operation.
	 */

	/*!
	 * A location for applications to store information that will be
	 * available in callbacks taking a WT_SESSION handle.
	 */
	void *app_private;

	/*!
	 * Close the session handle.
	 *
	 * This will release the resources associated with the session handle,
	 * including rolling back any active transactions and closing any
	 * cursors that remain open in the session.
	 *
	 * @snippet ex_all.c Close a session
	 *
	 * @param session the session handle
	 * @configempty{WT_SESSION.close, see dist/api_data.py}
	 * @errors
	 */
	int (*close)(WT_SESSION *session,
	    const char *config);

	/*!
	 * Reconfigure a session handle.
	 *
	 * @snippet ex_all.c Reconfigure a session
	 *
	 * WT_SESSION::reconfigure will fail if a transaction is in progress
	 * in the session.
	 *
	 * All cursors are reset.
	 *
	 * @param session the session handle
	 * @configstart{WT_SESSION.reconfigure, see dist/api_data.py}
	 * @config{isolation, the default isolation level for operations in this
	 * session., a string\, chosen from the following options: \c
	 * "read-uncommitted"\, \c "read-committed"\, \c "snapshot"; default \c
	 * read-committed.}
	 * @configend
	 * @errors
	 */
	int (*reconfigure)(WT_SESSION *session, const char *config);

	/*!
	 * Return information about an error as a string.
	 *
	 * @snippet ex_all.c Display an error thread safe
	 *
	 * @param session the session handle
	 * @param error a return value from a WiredTiger function
	 * @returns a string representation of the error
	 */
	const char *(*strerror)(WT_SESSION *session, int error);

	/*!
	 * @name Cursor handles
	 * @{
	 */

	/*!
	 * Open a new cursor on a data source or duplicate an existing cursor.
	 *
	 * @snippet ex_all.c Open a cursor
	 *
	 * An existing cursor can be duplicated by passing it as the \c to_dup
	 * parameter and setting the \c uri parameter to \c NULL:
	 *
	 * @snippet ex_all.c Duplicate a cursor
	 *
	 * Cursors being duplicated must have a key set, and successfully
	 * duplicated cursors are positioned at the same place in the data
	 * source as the original.
	 *
	 * Cursor handles should be discarded by calling WT_CURSOR::close.
	 *
	 * Cursors capable of supporting transactional operations operate in the
	 * context of the current transaction, if any.
	 *
	 * WT_SESSION::rollback_transaction implicitly resets all cursors.
	 *
	 * Cursors are relatively light-weight objects but may hold references
	 * to heavier-weight objects; applications should re-use cursors when
	 * possible, but instantiating new cursors is not so expensive that
	 * applications need to cache cursors at all cost.
	 *
	 * @param session the session handle
	 * @param uri the data source on which the cursor operates; cursors
	 *  are usually opened on tables, however, cursors can be opened on
	 *  any data source, regardless of whether it is ultimately stored
	 *  in a table.  Some cursor types may have limited functionality
	 *  (for example, they may be read-only or not support transactional
	 *  updates).  See @ref data_sources for more information.
	 *  <br>
	 *  @copydoc doc_cursor_types
	 * @param to_dup a cursor to duplicate
	 * @configstart{WT_SESSION.open_cursor, see dist/api_data.py}
	 * @config{append, append the value as a new record\, creating a new
	 * record number key; valid only for cursors with record number keys., a
	 * boolean flag; default \c false.}
	 * @config{bulk, configure the cursor for bulk-loading\, a fast\,
	 * initial load path (see @ref tune_bulk_load for more information).
	 * Bulk-load may only be used for newly created objects and cursors
	 * configured for bulk-load only support the WT_CURSOR::insert and
	 * WT_CURSOR::close methods.  When bulk-loading row-store objects\, keys
	 * must be loaded in sorted order.  The value is usually a true/false
	 * flag; when bulk-loading fixed-length column store objects\, the
	 * special value \c bitmap allows chunks of a memory resident bitmap to
	 * be loaded directly into a file by passing a \c WT_ITEM to
	 * WT_CURSOR::set_value where the \c size field indicates the number of
	 * records in the bitmap (as specified by the object's \c value_format
	 * configuration). Bulk-loaded bitmap values must end on a byte boundary
	 * relative to the bit count (except for the last set of values
	 * loaded)., a string; default \c false.}
	 * @config{checkpoint, the name of a checkpoint to open (the reserved
	 * name "WiredTigerCheckpoint" opens the most recent internal checkpoint
	 * taken for the object). The cursor does not support data
	 * modification., a string; default empty.}
	 * @config{dump, configure the cursor for dump format inputs and
	 * outputs: "hex" selects a simple hexadecimal format\, "json" selects a
	 * JSON format with each record formatted as fields named by column
	 * names if available\, and "print" selects a format where only
	 * non-printing characters are hexadecimal encoded.  These formats are
	 * compatible with the @ref util_dump and @ref util_load commands., a
	 * string\, chosen from the following options: \c "hex"\, \c "json"\, \c
	 * "print"; default empty.}
	 * @config{next_random, configure the cursor to return a pseudo-random
	 * record from the object; valid only for row-store cursors.  Cursors
	 * configured with \c next_random=true only support the WT_CURSOR::next
	 * and WT_CURSOR::close methods.  See @ref cursor_random for details., a
	 * boolean flag; default \c false.}
	 * @config{overwrite, configures whether the cursor's insert\, update
	 * and remove methods check the existing state of the record.  If \c
	 * overwrite is \c false\, WT_CURSOR::insert fails with
	 * ::WT_DUPLICATE_KEY if the record exists\, WT_CURSOR::update and
	 * WT_CURSOR::remove fail with ::WT_NOTFOUND if the record does not
	 * exist., a boolean flag; default \c true.}
	 * @config{raw, ignore the encodings for the key and value\, manage data
	 * as if the formats were \c "u". See @ref cursor_raw for details., a
	 * boolean flag; default \c false.}
	 * @config{readonly, only query operations are supported by this cursor.
	 * An error is returned if a modification is attempted using the cursor.
	 * The default is false for all cursor types except for log and metadata
	 * cursors., a boolean flag; default \c false.}
	 * @config{statistics, Specify the statistics to be gathered.  Choosing
	 * "all" gathers statistics regardless of cost and may include
	 * traversing on-disk files; "fast" gathers a subset of relatively
	 * inexpensive statistics.  The selection must agree with the database
	 * \c statistics configuration specified to ::wiredtiger_open or
	 * WT_CONNECTION::reconfigure.  For example\, "all" or "fast" can be
	 * configured when the database is configured with "all"\, but the
	 * cursor open will fail if "all" is specified when the database is
	 * configured with "fast"\, and the cursor open will fail in all cases
	 * when the database is configured with "none". If "size" is
	 * configured\, only the underlying size of the object on disk is filled
	 * in and the object is not opened.  If \c statistics is not
	 * configured\, the default configuration is the database configuration.
	 * The "clear" configuration resets statistics after gathering them\,
	 * where appropriate (for example\, a cache size statistic is not
	 * cleared\, while the count of cursor insert operations will be
	 * cleared). See @ref statistics for more information., a list\, with
	 * values chosen from the following options: \c "all"\, \c "fast"\, \c
	 * "clear"\, \c "size"; default empty.}
	 * @config{target, if non-empty\, backup the list of objects; valid only
	 * for a backup data source., a list of strings; default empty.}
	 * @configend
	 * @param[out] cursorp a pointer to the newly opened cursor
	 * @errors
	 */
	int (*open_cursor)(WT_SESSION *session,
	    const char *uri, WT_CURSOR *to_dup,
	    const char *config, WT_CURSOR **cursorp);
	/*! @} */

	/*!
	 * @name Table operations
	 * @{
	 */
	/*!
	 * Create a table, column group, index or file.
	 *
	 * @snippet ex_all.c Create a table
	 *
	 * @param session the session handle
	 * @param name the URI of the object to create, such as
	 * \c "table:stock". For a description of URI formats
	 * see @ref data_sources.
	 * @configstart{WT_SESSION.create, see dist/api_data.py}
	 * @config{allocation_size, the file unit allocation size\, in bytes\,
	 * must a power-of-two; smaller values decrease the file space required
	 * by overflow items\, and the default value of 4KB is a good choice
	 * absent requirements from the operating system or storage device., an
	 * integer between 512B and 128MB; default \c 4KB.}
	 * @config{app_metadata, application-owned metadata for this object., a
	 * string; default empty.}
	 * @config{block_allocation, configure block allocation.  Permitted
	 * values are \c "first" or \c "best"; the \c "first" configuration uses
	 * a first-available algorithm during block allocation\, the \c "best"
	 * configuration uses a best-fit algorithm., a string\, chosen from the
	 * following options: \c "first"\, \c "best"; default \c best.}
	 * @config{block_compressor, configure a compressor for file blocks.
	 * Permitted values are \c "none" or custom compression engine name
	 * created with WT_CONNECTION::add_compressor.  If WiredTiger has
	 * builtin support for \c "bzip2"\, \c "snappy"\, \c "lz4" or \c "zlib"
	 * compression\, these names are also available.  See @ref compression
	 * for more information., a string; default \c none.}
	 * @config{cache_resident, do not ever evict the object's pages from
	 * cache.  Not compatible with LSM tables; see @ref
	 * tuning_cache_resident for more information., a boolean flag; default
	 * \c false.}
	 * @config{checksum, configure block checksums; permitted values are
	 * <code>on</code> (checksum all blocks)\, <code>off</code> (checksum no
	 * blocks) and <code>uncompresssed</code> (checksum only blocks which
	 * are not compressed for any reason). The \c uncompressed setting is
	 * for applications which can rely on decompression to fail if a block
	 * has been corrupted., a string\, chosen from the following options: \c
	 * "on"\, \c "off"\, \c "uncompressed"; default \c uncompressed.}
	 * @config{colgroups, comma-separated list of names of column groups.
	 * Each column group is stored separately\, keyed by the primary key of
	 * the table.  If no column groups are specified\, all columns are
	 * stored together in a single file.  All value columns in the table
	 * must appear in at least one column group.  Each column group must be
	 * created with a separate call to WT_SESSION::create., a list of
	 * strings; default empty.}
	 * @config{collator, configure custom collation for keys.  Permitted
	 * values are \c "none" or a custom collator name created with
	 * WT_CONNECTION::add_collator., a string; default \c none.}
	 * @config{columns, list of the column names.  Comma-separated list of
	 * the form <code>(column[\,...])</code>. For tables\, the number of
	 * entries must match the total number of values in \c key_format and \c
	 * value_format.  For colgroups and indices\, all column names must
	 * appear in the list of columns for the table., a list of strings;
	 * default empty.}
	 * @config{dictionary, the maximum number of unique values remembered in
	 * the Btree row-store leaf page value dictionary; see @ref
	 * file_formats_compression for more information., an integer greater
	 * than or equal to 0; default \c 0.}
	 * @config{encryption = (, configure an encryptor for file blocks.  When
	 * a table is created\, its encryptor is not implicitly used for any
	 * related indices or column groups., a set of related configuration
	 * options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;keyid, An
	 * identifier that identifies a unique instance of the encryptor.  It is
	 * stored in clear text\, and thus is available when the wiredtiger
	 * database is reopened.  On the first use of a (name\, keyid)
	 * combination\, the WT_ENCRYPTOR::customize function is called with the
	 * keyid as an argument., a string; default empty.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;name, Permitted values are \c "none"
	 * or custom encryption engine name created with
	 * WT_CONNECTION::add_encryptor.  See @ref encryption for more
	 * information., a string; default \c none.}
	 * @config{ ),,}
	 * @config{exclusive, fail if the object exists.  When false (the
	 * default)\, if the object exists\, check that its settings match the
	 * specified configuration., a boolean flag; default \c false.}
	 * @config{extractor, configure custom extractor for indices.  Permitted
	 * values are \c "none" or an extractor name created with
	 * WT_CONNECTION::add_extractor., a string; default \c none.}
	 * @config{format, the file format., a string\, chosen from the
	 * following options: \c "btree"; default \c btree.}
	 * @config{huffman_key, configure Huffman encoding for keys.  Permitted
	 * values are \c "none"\, \c "english"\, \c "utf8<file>" or \c
	 * "utf16<file>". See @ref huffman for more information., a string;
	 * default \c none.}
	 * @config{huffman_value, configure Huffman encoding for values.
	 * Permitted values are \c "none"\, \c "english"\, \c "utf8<file>" or \c
	 * "utf16<file>". See @ref huffman for more information., a string;
	 * default \c none.}
	 * @config{immutable, configure the index to be immutable - that is an
	 * index is not changed by any update to a record in the table., a
	 * boolean flag; default \c false.}
	 * @config{internal_key_max, the largest key stored in an internal
	 * node\, in bytes.  If set\, keys larger than the specified size are
	 * stored as overflow items (which may require additional I/O to
	 * access). The default and the maximum allowed value are both one-tenth
	 * the size of a newly split internal page., an integer greater than or
	 * equal to 0; default \c 0.}
	 * @config{internal_key_truncate, configure internal key truncation\,
	 * discarding unnecessary trailing bytes on internal keys (ignored for
	 * custom collators)., a boolean flag; default \c true.}
	 * @config{internal_page_max, the maximum page size for internal nodes\,
	 * in bytes; the size must be a multiple of the allocation size and is
	 * significant for applications wanting to avoid excessive L2 cache
	 * misses while searching the tree.  The page maximum is the bytes of
	 * uncompressed data\, that is\, the limit is applied before any block
	 * compression is done., an integer between 512B and 512MB; default \c
	 * 4KB.}
	 * @config{key_format, the format of the data packed into key items.
	 * See @ref schema_format_types for details.  By default\, the
	 * key_format is \c 'u' and applications use WT_ITEM structures to
	 * manipulate raw byte arrays.  By default\, records are stored in
	 * row-store files: keys of type \c 'r' are record numbers and records
	 * referenced by record number are stored in column-store files., a
	 * format string; default \c u.}
	 * @config{leaf_key_max, the largest key stored in a leaf node\, in
	 * bytes.  If set\, keys larger than the specified size are stored as
	 * overflow items (which may require additional I/O to access). The
	 * default value is one-tenth the size of a newly split leaf page., an
	 * integer greater than or equal to 0; default \c 0.}
	 * @config{leaf_page_max, the maximum page size for leaf nodes\, in
	 * bytes; the size must be a multiple of the allocation size\, and is
	 * significant for applications wanting to maximize sequential data
	 * transfer from a storage device.  The page maximum is the bytes of
	 * uncompressed data\, that is\, the limit is applied before any block
	 * compression is done., an integer between 512B and 512MB; default \c
	 * 32KB.}
	 * @config{leaf_value_max, the largest value stored in a leaf node\, in
	 * bytes.  If set\, values larger than the specified size are stored as
	 * overflow items (which may require additional I/O to access). If the
	 * size is larger than the maximum leaf page size\, the page size is
	 * temporarily ignored when large values are written.  The default is
	 * one-half the size of a newly split leaf page., an integer greater
	 * than or equal to 0; default \c 0.}
	 * @config{log = (, the transaction log configuration for this object.
	 * Only valid if log is enabled in ::wiredtiger_open., a set of related
	 * configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;enabled, if false\, this object has
	 * checkpoint-level durability., a boolean flag; default \c true.}
	 * @config{ ),,}
	 * @config{lsm = (, options only relevant for LSM data sources., a set
	 * of related configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;auto_throttle, Throttle inserts into
	 * LSM trees if flushing to disk isn't keeping up., a boolean flag;
	 * default \c true.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;bloom, create bloom
	 * filters on LSM tree chunks as they are merged., a boolean flag;
	 * default \c true.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;bloom_bit_count,
	 * the number of bits used per item for LSM bloom filters., an integer
	 * between 2 and 1000; default \c 16.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;bloom_config, config string used when
	 * creating Bloom filter files\, passed to WT_SESSION::create., a
	 * string; default empty.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;bloom_hash_count, the number of hash
	 * values per item used for LSM bloom filters., an integer between 2 and
	 * 100; default \c 8.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;bloom_oldest,
	 * create a bloom filter on the oldest LSM tree chunk.  Only supported
	 * if bloom filters are enabled., a boolean flag; default \c false.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;chunk_count_limit, the maximum number
	 * of chunks to allow in an LSM tree.  This option automatically times
	 * out old data.  As new chunks are added old chunks will be removed.
	 * Enabling this option disables LSM background merges., an integer;
	 * default \c 0.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;chunk_max, the maximum
	 * size a single chunk can be.  Chunks larger than this size are not
	 * considered for further merges.  This is a soft limit\, and chunks
	 * larger than this value can be created.  Must be larger than
	 * chunk_size., an integer between 100MB and 10TB; default \c 5GB.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;chunk_size, the maximum size of the
	 * in-memory chunk of an LSM tree.  This limit is soft - it is possible
	 * for chunks to be temporarily larger than this value.  This overrides
	 * the \c memory_page_max setting., an integer between 512K and 500MB;
	 * default \c 10MB.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;merge_max, the
	 * maximum number of chunks to include in a merge operation., an integer
	 * between 2 and 100; default \c 15.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;merge_min, the minimum number of
	 * chunks to include in a merge operation.  If set to 0 or 1 half the
	 * value of merge_max is used., an integer no more than 100; default \c
	 * 0.}
	 * @config{ ),,}
	 * @config{memory_page_max, the maximum size a page can grow to in
	 * memory before being reconciled to disk.  The specified size will be
	 * adjusted to a lower bound of <code>50 * leaf_page_max</code>\, and an
	 * upper bound of <code>cache_size / 2</code>. This limit is soft - it
	 * is possible for pages to be temporarily larger than this value.  This
	 * setting is ignored for LSM trees\, see \c chunk_size., an integer
	 * between 512B and 10TB; default \c 5MB.}
	 * @config{os_cache_dirty_max, maximum dirty system buffer cache usage\,
	 * in bytes.  If non-zero\, schedule writes for dirty blocks belonging
	 * to this object in the system buffer cache after that many bytes from
	 * this object are written into the buffer cache., an integer greater
	 * than or equal to 0; default \c 0.}
	 * @config{os_cache_max, maximum system buffer cache usage\, in bytes.
	 * If non-zero\, evict object blocks from the system buffer cache after
	 * that many bytes from this object are read or written into the buffer
	 * cache., an integer greater than or equal to 0; default \c 0.}
	 * @config{prefix_compression, configure prefix compression on row-store
	 * leaf pages., a boolean flag; default \c false.}
	 * @config{prefix_compression_min, minimum gain before prefix
	 * compression will be used on row-store leaf pages., an integer greater
	 * than or equal to 0; default \c 4.}
	 * @config{split_pct, the Btree page split size as a percentage of the
	 * maximum Btree page size\, that is\, when a Btree page is split\, it
	 * will be split into smaller pages\, where each page is the specified
	 * percentage of the maximum Btree page size., an integer between 25 and
	 * 100; default \c 75.}
	 * @config{type, set the type of data source used to store a column
	 * group\, index or simple table.  By default\, a \c "file:" URI is
	 * derived from the object name.  The \c type configuration can be used
	 * to switch to a different data source\, such as LSM or an extension
	 * configured by the application., a string; default \c file.}
	 * @config{value_format, the format of the data packed into value items.
	 * See @ref schema_format_types for details.  By default\, the
	 * value_format is \c 'u' and applications use a WT_ITEM structure to
	 * manipulate raw byte arrays.  Value items of type 't' are bitfields\,
	 * and when configured with record number type keys\, will be stored
	 * using a fixed-length store., a format string; default \c u.}
	 * @configend
	 * @errors
	 */
	int (*create)(WT_SESSION *session,
	    const char *name, const char *config);

	/*!
	 * Compact a live row- or column-store btree or LSM tree.
	 *
	 * @snippet ex_all.c Compact a table
	 *
	 * @param session the session handle
	 * @param name the URI of the object to compact, such as
	 * \c "table:stock"
	 * @configstart{WT_SESSION.compact, see dist/api_data.py}
	 * @config{timeout, maximum amount of time to allow for compact in
	 * seconds.  The actual amount of time spent in compact may exceed the
	 * configured value.  A value of zero disables the timeout., an integer;
	 * default \c 1200.}
	 * @configend
	 * @errors
	 */
	int (*compact)(WT_SESSION *session,
	    const char *name, const char *config);

	/*!
	 * Drop (delete) an object.
	 *
	 * @snippet ex_all.c Drop a table
	 *
	 * @param session the session handle
	 * @param name the URI of the object to drop, such as \c "table:stock"
	 * @configstart{WT_SESSION.drop, see dist/api_data.py}
	 * @config{force, return success if the object does not exist., a
	 * boolean flag; default \c false.}
	 * @config{remove_files, should the underlying files be removed?., a
	 * boolean flag; default \c true.}
	 * @configend
	 * @ebusy_errors
	 */
	int (*drop)(WT_SESSION *session,
	    const char *name, const char *config);

	/*!
	 * Insert a ::WT_LOGREC_MESSAGE type record in the database log files
	 * (the database must be configured for logging when this method is
	 * called).
	 *
	 * @param session the session handle
	 * @param fmt a printf format specifier
	 * @errors
	 */
	int (*log_printf)(WT_SESSION *session, const char *fmt, ...);

	/*!
	 * Rename an object.
	 *
	 * @snippet ex_all.c Rename a table
	 *
	 * @param session the session handle
	 * @param uri the current URI of the object, such as \c "table:old"
	 * @param newuri the new URI of the object, such as \c "table:new"
	 * @configempty{WT_SESSION.rename, see dist/api_data.py}
	 * @ebusy_errors
	 */
	int (*rename)(WT_SESSION *session,
	    const char *uri, const char *newuri, const char *config);

	/*!
	 * Reset the session handle.
	 *
	 * This will reset all cursors associated with this session and clear
	 * any buffers that each cursor held. After this the buffers associated
	 * with the session will be discarded. The session can be re-used
	 * immediately after this call returns. If a transaction is running on
	 * this session, then this call will take no action and return a busy
	 * error.
	 *
	 * @snippet ex_all.c Reset the session
	 *
	 * @param session the session handle
	 * @ebusy_errors
	 */
	int (*reset)(WT_SESSION *session);

	/*!
	 * Salvage a file or table
	 *
	 * Salvage rebuilds the file, or files of which a table is comprised,
	 * discarding any corrupted file blocks.
	 *
	 * Previously deleted records may re-appear, and inserted records may
	 * disappear, when salvage is done, so salvage should not be run
	 * unless it is known to be necessary.  Normally, salvage should be
	 * called after a file or table has been corrupted, as reported by the
	 * WT_SESSION::verify method.
	 *
	 * Files are rebuilt in place, the salvage method overwrites the
	 * existing files.
	 *
	 * @snippet ex_all.c Salvage a table
	 *
	 * @param session the session handle
	 * @param name the URI of the file or table to salvage
	 * @configstart{WT_SESSION.salvage, see dist/api_data.py}
	 * @config{force, force salvage even of files that do not appear to be
	 * WiredTiger files., a boolean flag; default \c false.}
	 * @configend
	 * @ebusy_errors
	 */
	int (*salvage)(WT_SESSION *session,
	    const char *name, const char *config);

	/*!
	 * Truncate a file, table or cursor range.
	 *
	 * Truncate a file or table.
	 * @snippet ex_all.c Truncate a table
	 *
	 * Truncate a cursor range.  When truncating based on a cursor position,
	 * it is not required the cursor reference a record in the object, only
	 * that the key be set.  This allows applications to discard portions of
	 * the object name space without knowing exactly what records the object
	 * contains.
	 * @snippet ex_all.c Truncate a range
	 *
	 * @param session the session handle
	 * @param name the URI of the file or table to truncate
	 * @param start optional cursor marking the first record discarded;
	 * if <code>NULL</code>, the truncate starts from the beginning of
	 * the object
	 * @param stop optional cursor marking the last record discarded;
	 * if <code>NULL</code>, the truncate continues to the end of the
	 * object
	 * @configempty{WT_SESSION.truncate, see dist/api_data.py}
	 * @ebusy_errors
	 */
	int (*truncate)(WT_SESSION *session,
	    const char *name,
	    WT_CURSOR *start,
	    WT_CURSOR *stop,
	    const char *config);

	/*!
	 * Upgrade a file or table.
	 *
	 * Upgrade upgrades a file or table, if upgrade is required.
	 *
	 * @snippet ex_all.c Upgrade a table
	 *
	 * @param session the session handle
	 * @param name the URI of the file or table to upgrade
	 * @configempty{WT_SESSION.upgrade, see dist/api_data.py}
	 * @ebusy_errors
	 */
	int (*upgrade)(WT_SESSION *session,
	    const char *name, const char *config);

	/*!
	 * Verify a file or table.
	 *
	 * Verify reports if a file, or the files of which a table is
	 * comprised, have been corrupted.  The WT_SESSION::salvage method
	 * can be used to repair a corrupted file,
	 *
	 * @snippet ex_all.c Verify a table
	 *
	 * @param session the session handle
	 * @param name the URI of the file or table to verify
	 * @configstart{WT_SESSION.verify, see dist/api_data.py}
	 * @config{dump_address, Display addresses and page types as pages are
	 * verified\, using the application's message handler\, intended for
	 * debugging., a boolean flag; default \c false.}
	 * @config{dump_blocks, Display the contents of on-disk blocks as they
	 * are verified\, using the application's message handler\, intended for
	 * debugging., a boolean flag; default \c false.}
	 * @config{dump_offsets, Display the contents of specific on-disk
	 * blocks\, using the application's message handler\, intended for
	 * debugging., a list of strings; default empty.}
	 * @config{dump_pages, Display the contents of in-memory pages as they
	 * are verified\, using the application's message handler\, intended for
	 * debugging., a boolean flag; default \c false.}
	 * @config{dump_shape, Display the shape of the tree after
	 * verification\, using the application's message handler\, intended for
	 * debugging., a boolean flag; default \c false.}
	 * @config{strict, Treat any verification problem as an error; by
	 * default\, verify will warn\, but not fail\, in the case of errors
	 * that won't affect future behavior (for example\, a leaked block)., a
	 * boolean flag; default \c false.}
	 * @configend
	 * @ebusy_errors
	 */
	int (*verify)(WT_SESSION *session,
	    const char *name, const char *config);
	/*! @} */

	/*!
	 * @name Transactions
	 * @{
	 */
	/*!
	 * Start a transaction in this session.
	 *
	 * The transaction remains active until ended by
	 * WT_SESSION::commit_transaction or WT_SESSION::rollback_transaction.
	 * Operations performed on cursors capable of supporting transactional
	 * operations that are already open in this session, or which are opened
	 * before the transaction ends, will operate in the context of the
	 * transaction.
	 *
	 * WT_SESSION::begin_transaction will fail if a transaction is already
	 * in progress in the session.
	 *
	 * @snippet ex_all.c transaction commit/rollback
	 *
	 * @param session the session handle
	 * @configstart{WT_SESSION.begin_transaction, see dist/api_data.py}
	 * @config{isolation, the isolation level for this transaction; defaults
	 * to the session's isolation level., a string\, chosen from the
	 * following options: \c "read-uncommitted"\, \c "read-committed"\, \c
	 * "snapshot"; default empty.}
	 * @config{name, name of the transaction for tracing and debugging., a
	 * string; default empty.}
	 * @config{priority, priority of the transaction for resolving
	 * conflicts.  Transactions with higher values are less likely to
	 * abort., an integer between -100 and 100; default \c 0.}
	 * @config{snapshot, use a named\, in-memory snapshot\, see @ref
	 * transaction_named_snapshots., a string; default empty.}
	 * @config{sync, whether to sync log records when the transaction
	 * commits\, inherited from ::wiredtiger_open \c transaction_sync., a
	 * boolean flag; default empty.}
	 * @configend
	 * @errors
	 */
	int (*begin_transaction)(WT_SESSION *session, const char *config);

	/*!
	 * Commit the current transaction.
	 *
	 * A transaction must be in progress when this method is called.
	 *
	 * If WT_SESSION::commit_transaction returns an error, the transaction
	 * was rolled back, not committed.
	 *
	 * @snippet ex_all.c transaction commit/rollback
	 *
	 * @param session the session handle
	 * @configstart{WT_SESSION.commit_transaction, see dist/api_data.py}
	 * @config{sync, override whether to sync log records when the
	 * transaction commits\, inherited from ::wiredtiger_open \c
	 * transaction_sync., a string\, chosen from the following options: \c
	 * "background"\, \c "off"\, \c "on"; default empty.}
	 * @configend
	 * @errors
	 */
	int (*commit_transaction)(WT_SESSION *session, const char *config);

	/*!
	 * Roll back the current transaction.
	 *
	 * A transaction must be in progress when this method is called.
	 *
	 * All cursors are reset.
	 *
	 * @snippet ex_all.c transaction commit/rollback
	 *
	 * @param session the session handle
	 * @configempty{WT_SESSION.rollback_transaction, see dist/api_data.py}
	 * @errors
	 */
	int (*rollback_transaction)(WT_SESSION *session, const char *config);

	/*!
	 * Write a transactionally consistent snapshot of a database or set of
	 * objects.  The checkpoint includes all transactions committed before
	 * the checkpoint starts.  Additionally, checkpoints may optionally be
	 * discarded.
	 *
	 * @snippet ex_all.c Checkpoint examples
	 *
	 * @param session the session handle
	 * @configstart{WT_SESSION.checkpoint, see dist/api_data.py}
	 * @config{drop, specify a list of checkpoints to drop.  The list may
	 * additionally contain one of the following keys: \c "from=all" to drop
	 * all checkpoints\, \c "from=<checkpoint>" to drop all checkpoints
	 * after and including the named checkpoint\, or \c "to=<checkpoint>" to
	 * drop all checkpoints before and including the named checkpoint.
	 * Checkpoints cannot be dropped while a hot backup is in progress or if
	 * open in a cursor., a list of strings; default empty.}
	 * @config{force, by default\, checkpoints may be skipped if the
	 * underlying object has not been modified\, this option forces the
	 * checkpoint., a boolean flag; default \c false.}
	 * @config{name, if set\, specify a name for the checkpoint (note that
	 * checkpoints including LSM trees may not be named)., a string; default
	 * empty.}
	 * @config{target, if non-empty\, checkpoint the list of objects., a
	 * list of strings; default empty.}
	 * @configend
	 * @errors
	 */
	int (*checkpoint)(WT_SESSION *session, const char *config);

	/*!
	 * Manage named snapshot transactions. Use this API to create and drop
	 * named snapshots. Named snapshot transactions can be accessed via
	 * WT_CURSOR::open. See @ref transaction_named_snapshots.
	 *
	 * @snippet ex_all.c Snapshot examples
	 *
	 * @param session the session handle
	 * @configstart{WT_SESSION.snapshot, see dist/api_data.py}
	 * @config{drop = (, if non-empty\, specifies which snapshots to drop.
	 * Where a group of snapshots are being dropped\, the order is based on
	 * snapshot creation order not alphanumeric name order., a set of
	 * related configuration options defined below.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;all, drop all named snapshots., a
	 * boolean flag; default \c false.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;before, drop all snapshots up to but
	 * not including the specified name., a string; default empty.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;names, drop specific named
	 * snapshots., a list of strings; default empty.}
	 * @config{&nbsp;&nbsp;&nbsp;&nbsp;to, drop all snapshots up to and
	 * including the specified name., a string; default empty.}
	 * @config{
	 * ),,}
	 * @config{name, specify a name for the snapshot., a string; default
	 * empty.}
	 * @configend
	 * @errors
	 */
	int (*snapshot)(WT_SESSION *session, const char *config);

	/*!
	 * Return the transaction ID range pinned by the session handle.
	 *
	 * The ID range is approximate and is calculated based on the oldest
	 * ID needed for the active transaction in this session, compared
	 * to the newest transaction in the system.
	 *
	 * @snippet ex_all.c transaction pinned range
	 *
	 * @param session the session handle
	 * @param[out] range the range of IDs pinned by this session. Zero if
	 * there is no active transaction.
	 * @errors
	 */
	int (*transaction_pinned_range)(WT_SESSION* session, uint64_t *range);

	/*!
	 * Wait for a transaction to become synchronized.  This method is
	 * only useful when ::wiredtiger_open is configured with the
	 * \c transaction_sync setting disabled.  This method must be called
	 * when no transactions are active in the session.
	 *
	 * @snippet ex_all.c Transaction sync
	 *
	 * @param session the session handle
	 * @configstart{WT_SESSION.transaction_sync, see dist/api_data.py}
	 * @config{timeout_ms, maximum amount of time to wait for background
	 * sync to complete in milliseconds.  A value of zero disables the
	 * timeout and returns immediately.  The default waits forever., an
	 * integer; default \c .}
	 * @configend
	 * @errors
	 */
	int (*transaction_sync)(WT_SESSION *session, const char *config);
	/*! @} */
};



/*!
 * A WT_CURSOR handle is the interface to a cursor.
 *
 * Cursors allow data to be searched, iterated and modified, implementing the
 * CRUD (create, read, update and delete) operations.  Cursors are opened in
 * the context of a session.  If a transaction is started, cursors operate in
 * the context of the transaction until the transaction is resolved.
 *
 * Raw data is represented by key/value pairs of WT_ITEM structures, but
 * cursors can also provide access to fields within the key and value if the
 * formats are described in the WT_SESSION::create method.
 *
 * In the common case, a cursor is used to access records in a table.  However,
 * cursors can be used on subsets of tables (such as a single column or a
 * projection of multiple columns), as an interface to statistics, configuration
 * data or application-specific data sources.  See WT_SESSION::open_cursor for
 * more information.
 *
 * <b>Thread safety:</b> A WT_CURSOR handle is not usually shared between
 * threads, see @ref threads for more information.
 */
struct __wt_cursor {
	WT_SESSION *session;	/*!< The session handle for this cursor. */

	/*!
	 * The name of the data source for the cursor, matches the \c uri
	 * parameter to WT_SESSION::open_cursor used to open the cursor.
	 */
	const char *uri;

	/*!
	 * The format of the data packed into key items.  See @ref packing for
	 * details.  If not set, a default value of "u" is assumed, and
	 * applications must use WT_ITEM structures to manipulate untyped byte
	 * arrays.
	 */
	const char *key_format;

	/*!
	 * The format of the data packed into value items.  See @ref packing
	 * for details.  If not set, a default value of "u" is assumed, and
	 * applications must use WT_ITEM structures to manipulate untyped byte
	 * arrays.
	 */
	const char *value_format;

	/*!
	 * @name Data access
	 * @{
	 */
	/*!
	 * Get the key for the current record.
	 *
	 * @snippet ex_all.c Get the cursor's string key
	 *
	 * @snippet ex_all.c Get the cursor's record number key
	 *
	 * @param cursor the cursor handle
	 * @param ... pointers to hold key fields corresponding to
	 * WT_CURSOR::key_format.
	 * @errors
	 */
	int (*get_key)(WT_CURSOR *cursor, ...);

	/*!
	 * Get the value for the current record.
	 *
	 * @snippet ex_all.c Get the cursor's string value
	 *
	 * @snippet ex_all.c Get the cursor's raw value
	 *
	 * @param cursor the cursor handle
	 * @param ... pointers to hold value fields corresponding to
	 * WT_CURSOR::value_format.
	 * @errors
	 */
	int (*get_value)(WT_CURSOR *cursor, ...);

	/*!
	 * Set the key for the next operation.
	 *
	 * @snippet ex_all.c Set the cursor's string key
	 *
	 * @snippet ex_all.c Set the cursor's record number key
	 *
	 * @param cursor the cursor handle
	 * @param ... key fields corresponding to WT_CURSOR::key_format.
	 *
	 * If an error occurs during this operation, a flag will be set in the
	 * cursor, and the next operation to access the key will fail.  This
	 * simplifies error handling in applications.
	 */
	void (*set_key)(WT_CURSOR *cursor, ...);

	/*!
	 * Set the value for the next operation.
	 *
	 * @snippet ex_all.c Set the cursor's string value
	 *
	 * @snippet ex_all.c Set the cursor's raw value
	 *
	 * @param cursor the cursor handle
	 * @param ... value fields corresponding to WT_CURSOR::value_format.
	 *
	 * If an error occurs during this operation, a flag will be set in the
	 * cursor, and the next operation to access the value will fail.  This
	 * simplifies error handling in applications.
	 */
	void (*set_value)(WT_CURSOR *cursor, ...);
	/*! @} */

	/*!
	 * @name Cursor positioning
	 * @{
	 */
	/*!
	 * Return the ordering relationship between two cursors: both cursors
	 * must have the same data source and have valid keys. (When testing
	 * only for equality, WT_CURSOR::equals may be faster.)
	 *
	 * @snippet ex_all.c Cursor comparison
	 *
	 * @param cursor the cursor handle
	 * @param other another cursor handle
	 * @param comparep the status of the comparison: < 0 if
	 * <code>cursor</code> refers to a key that appears before
	 * <code>other</code>, 0 if the cursors refer to the same key,
	 * and > 0 if <code>cursor</code> refers to a key that appears after
	 * <code>other</code>.
	 * @errors
	 */
	int (*compare)(WT_CURSOR *cursor, WT_CURSOR *other, int *comparep);

	/*!
	 * Return the ordering relationship between two cursors, testing only
	 * for equality: both cursors must have the same data source and have
	 * valid keys.
	 *
	 * @snippet ex_all.c Cursor equality
	 *
	 * @param cursor the cursor handle
	 * @param other another cursor handle
	 * @param[out] equalp the status of the comparison: 1 if the cursors
	 * refer to the same key, otherwise 0.
	 * @errors
	 */
	int (*equals)(WT_CURSOR *cursor, WT_CURSOR *other, int *equalp);

	/*!
	 * Return the next record.
	 *
	 * @snippet ex_all.c Return the next record
	 *
	 * @param cursor the cursor handle
	 * @errors
	 */
	int (*next)(WT_CURSOR *cursor);

	/*!
	 * Return the previous record.
	 *
	 * @snippet ex_all.c Return the previous record
	 *
	 * @param cursor the cursor handle
	 * @errors
	 */
	int (*prev)(WT_CURSOR *cursor);

	/*!
	 * Reset the cursor. Any resources held by the cursor are released,
	 * and the cursor's key and position are no longer valid. Subsequent
	 * iterations with WT_CURSOR::next will move to the first record, or
	 * with WT_CURSOR::prev will move to the last record.
	 *
	 * In the case of a statistics cursor, resetting the cursor refreshes
	 * the statistics information returned.
	 *
	 * @snippet ex_all.c Reset the cursor
	 *
	 * @param cursor the cursor handle
	 * @errors
	 */
	int (*reset)(WT_CURSOR *cursor);

	/*!
	 * Return the record matching the key. The key must first be set.
	 *
	 * @snippet ex_all.c Search for an exact match
	 *
	 * On success, the cursor ends positioned at the returned record; to
	 * minimize cursor resources, the WT_CURSOR::reset method should be
	 * called as soon as the record has been retrieved and the cursor no
	 * longer needs that position.
	 *
	 * @param cursor the cursor handle
	 * @errors
	 */
	int (*search)(WT_CURSOR *cursor);

	/*!
	 * Return the record matching the key if it exists, or an adjacent
	 * record.  An adjacent record is either the smallest record larger
	 * than the key or the largest record smaller than the key (in other
	 * words, a logically adjacent key).
	 *
	 * The key must first be set.
	 *
	 * An example of a search for an exact or adjacent match:
	 *
	 * @snippet ex_all.c Search for an exact or adjacent match
	 *
	 * An example of a forward scan through the table, where all keys
	 * greater than or equal to a specified prefix are included in the
	 * scan:
	 *
	 * @snippet ex_all.c Forward scan greater than or equal
	 *
	 * An example of a backward scan through the table, where all keys
	 * less than a specified prefix are included in the scan:
	 *
	 * @snippet ex_all.c Backward scan less than
	 *
	 * On success, the cursor ends positioned at the returned record; to
	 * minimize cursor resources, the WT_CURSOR::reset method should be
	 * called as soon as the record has been retrieved and the cursor no
	 * longer needs that position.
	 *
	 * @param cursor the cursor handle
	 * @param exactp the status of the search: 0 if an exact match is
	 * found, < 0 if a smaller key is returned, > 0 if a larger key is
	 * returned
	 * @errors
	 */
	int (*search_near)(WT_CURSOR *cursor, int *exactp);
	/*! @} */

	/*!
	 * @name Data modification
	 * @{
	 */
	/*!
	 * Insert a record and optionally update an existing record.
	 *
	 * If the cursor was configured with "overwrite=true" (the default),
	 * both the key and value must be set; if the record already exists,
	 * the key's value will be updated, otherwise, the record will be
	 * inserted.
	 *
	 * @snippet ex_all.c Insert a new record or overwrite an existing record
	 *
	 * If the cursor was not configured with "overwrite=true", both the key
	 * and value must be set and the record must not already exist; the
	 * record will be inserted.
	 *
	 * @snippet ex_all.c Insert a new record and fail if the record exists
	 *
	 * If a cursor with record number keys was configured with
	 * "append=true" (not the default), the value must be set; a new record
	 * will be appended and the record number set as the cursor key value.
	 *
	 * @snippet ex_all.c Insert a new record and assign a record number
	 *
	 * The cursor ends with no position, and a subsequent call to the
	 * WT_CURSOR::next (WT_CURSOR::prev) method will iterate from the
	 * beginning (end) of the table.
	 *
	 * Inserting a new record after the current maximum record in a
	 * fixed-length bit field column-store (that is, a store with an
	 * 'r' type key and 't' type value) may implicitly create the missing
	 * records as records with a value of 0.
	 *
	 * When loading a large amount of data into a new object, using
	 * a cursor with the \c bulk configuration string enabled and
	 * loading the data in sorted order will be much faster than doing
	 * out-of-order inserts.  See @ref tune_bulk_load for more information.
	 *
	 * The maximum length of a single column stored in a table is not fixed
	 * (as it partially depends on the underlying file configuration), but
	 * is always a small number of bytes less than 4GB.
	 *
	 * @param cursor the cursor handle
	 * @errors
	 * In particular, if \c overwrite is not configured and a record with
	 * the specified key already exists, ::WT_DUPLICATE_KEY is returned.
	 */
	int (*insert)(WT_CURSOR *cursor);

	/*!
	 * Update an existing record and optionally insert a record.
	 *
	 * If the cursor was configured with "overwrite=true" (the default),
	 * both the key and value must be set; if the record already exists, the
	 * key's value will be updated, otherwise, the record will be inserted.
	 *
	 * @snippet ex_all.c Update an existing record or insert a new record
	 *
	 * If the cursor was not configured with "overwrite=true", both the key
	 * and value must be set and the record must already exist; the
	 * record will be updated.
	 *
	 * @snippet ex_all.c Update an existing record and fail if DNE
	 *
	 * On success, the cursor ends positioned at the modified record; to
	 * minimize cursor resources, the WT_CURSOR::reset method should be
	 * called as soon as the cursor no longer needs that position.
	 *
	 * The maximum length of a single column stored in a table is not fixed
	 * (as it partially depends on the underlying file configuration), but
	 * is always a small number of bytes less than 4GB.
	 *
	 * @param cursor the cursor handle
	 * @errors
	 * In particular, if \c overwrite is not configured and no record with
	 * the specified key exists, ::WT_NOTFOUND is returned.
	 */
	int (*update)(WT_CURSOR *cursor);

	/*!
	 * Remove a record.
	 *
	 * If the cursor was configured with "overwrite=true" (the default),
	 * the key must be set; the key's record will be removed if it exists,
	 * no error will be returned if the record does not exist.
	 *
	 * @snippet ex_all.c Remove a record
	 *
	 * If the cursor was not configured with "overwrite=true", the key must
	 * be set and the key's record must exist; the record will be removed.
	 *
	 * @snippet ex_all.c Remove a record and fail if DNE
	 *
	 * Removing a record in a fixed-length bit field column-store
	 * (that is, a store with an 'r' type key and 't' type value) is
	 * identical to setting the record's value to 0.
	 *
	 * On success, the cursor ends positioned at the removed record; to
	 * minimize cursor resources, the WT_CURSOR::reset method should be
	 * called as soon as the cursor no longer needs that position.
	 *
	 * @param cursor the cursor handle
	 * @errors
	 * In particular, if \c overwrite is not configured and no record with
	 * the specified key exists, ::WT_NOTFOUND is returned.
	 */
	int (*remove)(WT_CURSOR *cursor);
	/*! @} */

	/*!
	 * Close the cursor.
	 *
	 * This releases the resources associated with the cursor handle.
	 * Cursors are closed implicitly by ending the enclosing connection or
	 * closing the session in which they were opened.
	 *
	 * @snippet ex_all.c Close the cursor
	 *
	 * @param cursor the cursor handle
	 * @errors
	 */
	int (*close)(WT_CURSOR *cursor);

	/*!
	 * Reconfigure the cursor.
	 *
	 * The cursor is reset.
	 *
	 * @snippet ex_all.c Reconfigure a cursor
	 *
	 * @param cursor the cursor handle
	 * @configstart{WT_CURSOR.reconfigure, see dist/api_data.py}
	 * @config{append, append the value as a new record\, creating a new
	 * record number key; valid only for cursors with record number keys., a
	 * boolean flag; default \c false.}
	 * @config{overwrite, configures whether the cursor's insert\, update
	 * and remove methods check the existing state of the record.  If \c
	 * overwrite is \c false\, WT_CURSOR::insert fails with
	 * ::WT_DUPLICATE_KEY if the record exists\, WT_CURSOR::update and
	 * WT_CURSOR::remove fail with ::WT_NOTFOUND if the record does not
	 * exist., a boolean flag; default \c true.}
	 * @configend
	 * @errors
	 */
	int (*reconfigure)(WT_CURSOR *cursor, const char *config);

	/*
	 * Protected fields, only to be used by cursor implementations.
	 */

	/*
	 * !!!
	 * Explicit representations of structures from queue.h.
	 * TAILQ_ENTRY(wt_cursor) q;
	 */
	struct {
		WT_CURSOR *tqe_next;
		WT_CURSOR **tqe_prev;
	} q;				/* Linked list of WT_CURSORs. */

	uint64_t recno;			/* Record number, normal and raw mode */
	uint8_t raw_recno_buf[17];

	void	*json_private;		/* JSON specific storage */
	void	*lang_private;		/* Language specific private storage */

        WT_ITEM key;
        WT_ITEM value;
	int saved_err;			/* Saved error in set_{key,value}. */
	/*
	 * URI used internally, may differ from the URI provided by the
	 * user on open.
	 */
	const char *internal_uri;
};


/*!
 * A raw item of data to be managed, including a pointer to the data and a
 * length.
 *
 * WT_ITEM structures do not need to be cleared before use.
 */
struct __wt_item {
	/*!
	 * The memory reference of the data item.
	 *
	 * For items returned by a WT_CURSOR, the pointer is only valid until
	 * the next operation on that cursor.  Applications that need to keep
	 * an item across multiple cursor operations must make a copy.
	 */
	const void *data;

	/*!
	 * The number of bytes in the data item.
	 *
	 * The maximum length of a single column stored in a table is not fixed
	 * (as it partially depends on the underlying file configuration), but
	 * is always a small number of bytes less than 4GB.
	 */
	size_t size;

	/* This appears in the middle of the struct to avoid padding. */
	/*! Object flags (internal use). */
	uint32_t flags;

	/*! Managed memory chunk (internal use). */
	void *mem;
	/*! Managed memory size (internal use). */
	size_t memsize;
};
