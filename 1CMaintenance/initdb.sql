CREATE TABLE IF NOT EXISTS InfoBase (
	name	TEXT	NOT NULL PRIMARY KEY,
	usr		TEXT,
	pass	TEXT,
	dbs		TEXT	NOT NULL CHECK (dbs in ('1С', 'PostgreSQL')),
	path	TEXT,
	host	TEXT,
	port	INTEGER	CHECK (port < 65536 and port > 0),
	db		TEXT,
	extusr	TEXT,
	extpass	TEXT
);

CREATE TABLE IF NOT EXISTS Param (
	name	TEXT	NOT NULL PRIMARY KEY,
	value	TEXT
);

CREATE TABLE IF NOT EXISTS Op (
	name	TEXT	NOT NULL PRIMARY KEY
);

CREATE TABLE IF NOT EXISTS Task (
	batch	TEXT	NOT NULL,
	ib		TEXT,
	op		TEXT,
	time	TEXT	NOT NULL,
	PRIMARY KEY (batch, ib, op),
	FOREIGN KEY (ib) REFERENCES InfoBase (name),
	FOREIGN KEY (op) REFERENCES Op (name)
);
			
INSERT INTO Op
VALUES ('Выгрузить ИБ'),
	('Исправить БД'),
	('Копировать БД'),
	('Архивировать журнал рег.');