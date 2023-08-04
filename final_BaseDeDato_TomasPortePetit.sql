create database Sube;
use Sube;

create table USERS(
IdUsers integer primary key auto_increment not null,
dni integer not null,
userName varchar(15) not null,
balance integer not null
);
create table destiny(
IdDestiny integer primary key auto_increment not null,
destinyName varchar(15) not null
);
create table transport(
IdTransport integer primary key auto_increment not null,
transportName varchar(15) not null
);
create table actualDestiny(
IdUsers integer not null, 
IdDestiny integer not null, 
CONSTRAINT FK_IdUsers FOREIGN KEY(IdUsers) REFERENCES USERS(IdUsers),
CONSTRAINT FK_IdDestiny FOREIGN KEY(IdDestiny) REFERENCES destiny(IdDestiny)
);
create table lastTransportUsed(
IdUsers integer not null, 
IdTransport integer not null, 
CONSTRAINT FK_IdUser FOREIGN KEY(IdUsers) REFERENCES USERS(IdUsers),
CONSTRAINT FK_IdTransport FOREIGN KEY(IdTransport) REFERENCES transport(IdTransport)
);
