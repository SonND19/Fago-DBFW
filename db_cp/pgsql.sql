--
-- PostgreSQL database dump
--

-- Dumped from database version 14.8 (Ubuntu 14.8-0ubuntu0.22.04.1)
-- Dumped by pg_dump version 14.8 (Ubuntu 14.8-0ubuntu0.22.04.1)

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- Name: admin; Type: TABLE; Schema: public; Owner: green
--

CREATE TABLE public.admin (
    adminid integer NOT NULL,
    name character varying(50) DEFAULT ''::character varying NOT NULL,
    pwd character varying(50) DEFAULT ''::character varying NOT NULL,
    email character varying(50) DEFAULT ''::character varying NOT NULL
);


ALTER TABLE public.admin OWNER TO green;

--
-- Name: admin_adminid_seq; Type: SEQUENCE; Schema: public; Owner: green
--

CREATE SEQUENCE public.admin_adminid_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.admin_adminid_seq OWNER TO green;

--
-- Name: admin_adminid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: green
--

ALTER SEQUENCE public.admin_adminid_seq OWNED BY public.admin.adminid;


--
-- Name: alert; Type: TABLE; Schema: public; Owner: green
--

CREATE TABLE public.alert (
    alertid integer NOT NULL,
    agroupid integer DEFAULT 0,
    event_time timestamp without time zone,
    risk smallint DEFAULT '0'::smallint NOT NULL,
    block smallint DEFAULT '0'::smallint NOT NULL,
    dbuser character varying(50) DEFAULT ''::character varying NOT NULL,
    userip character varying(50) DEFAULT ''::character varying NOT NULL,
    query text NOT NULL,
    reason text NOT NULL
);


ALTER TABLE public.alert OWNER TO green;

--
-- Name: alert_alertid_seq; Type: SEQUENCE; Schema: public; Owner: green
--

CREATE SEQUENCE public.alert_alertid_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.alert_alertid_seq OWNER TO green;

--
-- Name: alert_alertid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: green
--

ALTER SEQUENCE public.alert_alertid_seq OWNED BY public.alert.alertid;


--
-- Name: alert_group; Type: TABLE; Schema: public; Owner: green
--

CREATE TABLE public.alert_group (
    agroupid integer NOT NULL,
    proxyid integer DEFAULT 1 NOT NULL,
    db_name character varying(50) DEFAULT ''::character varying NOT NULL,
    update_time timestamp without time zone,
    status smallint DEFAULT 0 NOT NULL,
    pattern text NOT NULL
);


ALTER TABLE public.alert_group OWNER TO green;

--
-- Name: alert_group_agroupid_seq; Type: SEQUENCE; Schema: public; Owner: green
--

CREATE SEQUENCE public.alert_group_agroupid_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.alert_group_agroupid_seq OWNER TO green;

--
-- Name: alert_group_agroupid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: green
--

ALTER SEQUENCE public.alert_group_agroupid_seq OWNED BY public.alert_group.agroupid;


--
-- Name: db_perm; Type: TABLE; Schema: public; Owner: green
--

CREATE TABLE public.db_perm (
    dbpid integer NOT NULL,
    proxyid integer DEFAULT 0 NOT NULL,
    db_name character varying(50) NOT NULL,
    perms bigint DEFAULT '0'::bigint NOT NULL,
    perms2 bigint DEFAULT '0'::bigint NOT NULL,
    status smallint DEFAULT '0'::smallint NOT NULL,
    sysdbtype character varying(20) DEFAULT 'user_db'::character varying NOT NULL,
    status_changed timestamp without time zone
);


ALTER TABLE public.db_perm OWNER TO green;

--
-- Name: db_perm_dbpid_seq; Type: SEQUENCE; Schema: public; Owner: green
--

CREATE SEQUENCE public.db_perm_dbpid_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.db_perm_dbpid_seq OWNER TO green;

--
-- Name: db_perm_dbpid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: green
--

ALTER SEQUENCE public.db_perm_dbpid_seq OWNED BY public.db_perm.dbpid;


--
-- Name: info; Type: TABLE; Schema: public; Owner: green
--

CREATE TABLE public.info (
    id integer,
    name character varying(50) DEFAULT ''::character varying NOT NULL,
    pwd character varying(50) DEFAULT ''::character varying NOT NULL,
    email character varying(50) DEFAULT ''::character varying NOT NULL
);


ALTER TABLE public.info OWNER TO green;

--
-- Name: proxy; Type: TABLE; Schema: public; Owner: green
--

CREATE TABLE public.proxy (
    proxyid integer NOT NULL,
    proxyname character varying(50) DEFAULT ''::character varying NOT NULL,
    frontend_ip character varying(20) DEFAULT ''::character varying NOT NULL,
    frontend_port smallint DEFAULT 0 NOT NULL,
    backend_server character varying(50) DEFAULT ''::character varying NOT NULL,
    backend_ip character varying(20) DEFAULT ''::character varying NOT NULL,
    backend_port smallint DEFAULT 0 NOT NULL,
    dbtype character varying(20) DEFAULT 'mysql'::character varying NOT NULL,
    status smallint DEFAULT '1'::smallint NOT NULL
);


ALTER TABLE public.proxy OWNER TO green;

--
-- Name: proxy_proxyid_seq; Type: SEQUENCE; Schema: public; Owner: green
--

CREATE SEQUENCE public.proxy_proxyid_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.proxy_proxyid_seq OWNER TO green;

--
-- Name: proxy_proxyid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: green
--

ALTER SEQUENCE public.proxy_proxyid_seq OWNED BY public.proxy.proxyid;


--
-- Name: query; Type: TABLE; Schema: public; Owner: green
--

CREATE TABLE public.query (
    queryid integer NOT NULL,
    proxyid integer DEFAULT 0 NOT NULL,
    perm smallint DEFAULT 1 NOT NULL,
    db_name character varying(50) NOT NULL,
    query text NOT NULL
);


ALTER TABLE public.query OWNER TO green;

--
-- Name: query_queryid_seq; Type: SEQUENCE; Schema: public; Owner: green
--

CREATE SEQUENCE public.query_queryid_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER TABLE public.query_queryid_seq OWNER TO green;

--
-- Name: query_queryid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: green
--

ALTER SEQUENCE public.query_queryid_seq OWNED BY public.query.queryid;


--
-- Name: admin adminid; Type: DEFAULT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.admin ALTER COLUMN adminid SET DEFAULT nextval('public.admin_adminid_seq'::regclass);


--
-- Name: alert alertid; Type: DEFAULT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.alert ALTER COLUMN alertid SET DEFAULT nextval('public.alert_alertid_seq'::regclass);


--
-- Name: alert_group agroupid; Type: DEFAULT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.alert_group ALTER COLUMN agroupid SET DEFAULT nextval('public.alert_group_agroupid_seq'::regclass);


--
-- Name: db_perm dbpid; Type: DEFAULT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.db_perm ALTER COLUMN dbpid SET DEFAULT nextval('public.db_perm_dbpid_seq'::regclass);


--
-- Name: proxy proxyid; Type: DEFAULT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.proxy ALTER COLUMN proxyid SET DEFAULT nextval('public.proxy_proxyid_seq'::regclass);


--
-- Name: query queryid; Type: DEFAULT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.query ALTER COLUMN queryid SET DEFAULT nextval('public.query_queryid_seq'::regclass);


--
-- Data for Name: admin; Type: TABLE DATA; Schema: public; Owner: green
--

COPY public.admin (adminid, name, pwd, email) FROM stdin;
1	admin	37fa265330ad83eaa879efb1e2db6380896cf639	
\.


--
-- Data for Name: alert; Type: TABLE DATA; Schema: public; Owner: green
--

COPY public.alert (alertid, agroupid, event_time, risk, block, dbuser, userip, query, reason) FROM stdin;
\.


--
-- Data for Name: alert_group; Type: TABLE DATA; Schema: public; Owner: green
--

COPY public.alert_group (agroupid, proxyid, db_name, update_time, status, pattern) FROM stdin;
\.


--
-- Data for Name: db_perm; Type: TABLE DATA; Schema: public; Owner: green
--

COPY public.db_perm (dbpid, proxyid, db_name, perms, perms2, status, sysdbtype, status_changed) FROM stdin;
1	0	default mysql db	0	0	0	default_mysql	\N
2	0	no-name mysql db	0	0	0	empty_mysql	\N
3	0	default pgsql db	0	0	0	default_pgsql	\N
\.


--
-- Data for Name: info; Type: TABLE DATA; Schema: public; Owner: green
--

COPY public.info (id, name, pwd, email) FROM stdin;
1	ad1	123asdfxcaxa	
2	ad2	123afwgwefxcaxa	
4	ad3	123afwg2656xa	
5	son	adqwrq	
1	ad1	123asdfxcaxa	
2	ad2	123afwgwefxcaxa	
4	ad3	123afwg2656xa	
5	son	adqwrq	
\.


--
-- Data for Name: proxy; Type: TABLE DATA; Schema: public; Owner: green
--

COPY public.proxy (proxyid, proxyname, frontend_ip, frontend_port, backend_server, backend_ip, backend_port, dbtype, status) FROM stdin;
1	Default MySQL Proxy	127.0.0.1	3305	localhost	127.0.0.1	3306	mysql	1
2	Default PgSQL Proxy	127.0.0.1	5431	localhost	127.0.0.1	5432	pgsql	1
\.


--
-- Data for Name: query; Type: TABLE DATA; Schema: public; Owner: green
--

COPY public.query (queryid, proxyid, perm, db_name, query) FROM stdin;
\.


--
-- Name: admin_adminid_seq; Type: SEQUENCE SET; Schema: public; Owner: green
--

SELECT pg_catalog.setval('public.admin_adminid_seq', 1, true);


--
-- Name: alert_alertid_seq; Type: SEQUENCE SET; Schema: public; Owner: green
--

SELECT pg_catalog.setval('public.alert_alertid_seq', 1, false);


--
-- Name: alert_group_agroupid_seq; Type: SEQUENCE SET; Schema: public; Owner: green
--

SELECT pg_catalog.setval('public.alert_group_agroupid_seq', 1, false);


--
-- Name: db_perm_dbpid_seq; Type: SEQUENCE SET; Schema: public; Owner: green
--

SELECT pg_catalog.setval('public.db_perm_dbpid_seq', 3, true);


--
-- Name: proxy_proxyid_seq; Type: SEQUENCE SET; Schema: public; Owner: green
--

SELECT pg_catalog.setval('public.proxy_proxyid_seq', 2, true);


--
-- Name: query_queryid_seq; Type: SEQUENCE SET; Schema: public; Owner: green
--

SELECT pg_catalog.setval('public.query_queryid_seq', 1, false);


--
-- Name: admin admin_pkey; Type: CONSTRAINT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.admin
    ADD CONSTRAINT admin_pkey PRIMARY KEY (adminid);


--
-- Name: alert_group alert_group_pkey; Type: CONSTRAINT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.alert_group
    ADD CONSTRAINT alert_group_pkey PRIMARY KEY (agroupid);


--
-- Name: alert alert_pkey; Type: CONSTRAINT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.alert
    ADD CONSTRAINT alert_pkey PRIMARY KEY (alertid);


--
-- Name: db_perm db_perm_pkey; Type: CONSTRAINT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.db_perm
    ADD CONSTRAINT db_perm_pkey PRIMARY KEY (dbpid);


--
-- Name: proxy proxy_pkey; Type: CONSTRAINT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.proxy
    ADD CONSTRAINT proxy_pkey PRIMARY KEY (proxyid);


--
-- Name: query query_pkey; Type: CONSTRAINT; Schema: public; Owner: green
--

ALTER TABLE ONLY public.query
    ADD CONSTRAINT query_pkey PRIMARY KEY (queryid);


--
-- Name: alert_agroupid_idx; Type: INDEX; Schema: public; Owner: green
--

CREATE INDEX alert_agroupid_idx ON public.alert USING btree (agroupid);


--
-- Name: alert_group_idx; Type: INDEX; Schema: public; Owner: green
--

CREATE INDEX alert_group_idx ON public.alert_group USING btree (update_time);


--
-- Name: db_perm_idx; Type: INDEX; Schema: public; Owner: green
--

CREATE INDEX db_perm_idx ON public.db_perm USING btree (proxyid, db_name);


--
-- Name: query_idx; Type: INDEX; Schema: public; Owner: green
--

CREATE INDEX query_idx ON public.query USING btree (proxyid, db_name);


--
-- Name: TABLE info; Type: ACL; Schema: public; Owner: green
--

GRANT SELECT ON TABLE public.info TO son;


--
-- PostgreSQL database dump complete
--

