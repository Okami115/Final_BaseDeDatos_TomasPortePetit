create database Sube;
use Sube;

create table destiny(
IdDestiny integer primary key auto_increment not null,
destinyName varchar(15) not null
);
create table transport(
IdTransport integer primary key auto_increment not null,
transportName varchar(15) not null
);
create table actualDestiny(
IdUser integer not null,
IdDestiny integer not null
);
create table lastTransportUsed(
IdUser integer not null,
IdTransport integer not null
);

select * from USERS;
select * from destiny;
select * from actualDestiny;
select * from transport;
select * from lastTransportUsed;
