CREATE TABLE IF NOT EXISTS InfoBase (
	name	TEXT	PRIMARY KEY,
	usr		TEXT,
	pass	TEXT,
	dbs		TEXT	NOT NULL CHECK (dbs in ('1С', 'PostgreSQL')),
	path	TEXT,
	host	TEXT,
	port	INTEGER	CHECK (port <= 65535 and port >= 1),
	db		TEXT,
	extusr	TEXT,
	extpass	TEXT
);

CREATE TABLE IF NOT EXISTS Param (
	name	TEXT	PRIMARY KEY,
	value	TEXT
);

CREATE TABLE IF NOT EXISTS Op (
	name	TEXT	PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS Task (
	id		INTEGER	PRIMARY KEY,
	time	TEXT	NOT NULL,
	ib		TEXT,
	op		TEXT,
	taskid	TEXT	NOT NULL,
	FOREIGN KEY (ib) REFERENCES InfoBase (name),
	FOREIGN KEY (op) REFERENCES Op (name)
);
			
INSERT INTO Op
VALUES ('Выгрузить ИБ'),
	('Исправить БД'),
	('Копировать БД'),
	('Архивировать журнал рег.');