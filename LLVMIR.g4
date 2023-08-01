grammar LLVMIR;

compilationUnit: topLevelEntity* EOF;

topLevelEntity:
	globalDecl
	| globalDef
	| funcDecl
	| funcDef;


//全局变量声明定义
globalDecl:
	GlobalIdent '='  immutable type ;
globalDef:
	GlobalIdent '='  immutable type constant;
//need

immutable: 
	'constant' | 'global';

//全局函数声明定义
funcDecl: 
	'declare' funcHeader;//函数声明
funcDef: 
	'define' funcHeader funcBody;//函数定义

funcHeader:
     type GlobalIdent
		'(' params ')';
funcBody: 
	'{' basicBlock+ '}';
//基本块
basicBlock: 
	LabelIdent? instruction* terminator;
instruction:
	localDefInst
	| valueInstruction
	| storeInst;
terminator:
	retTerm
	| brTerm
	| condBrTerm;

localDefInst: LocalIdent '=' valueInstruction;
mathInstruction:
	'add'  concreteType value ',' value			#addInst
	|'fadd' concreteType value ',' value		#faddInst
	|'sub'  concreteType value ',' value		#subInst
	|'fsub' concreteType value ',' value		#fsubInst
	|'mul'  concreteType value ',' value		#mulInst
	|'fmul' concreteType value ',' value		#fmulInst
	|'udiv' concreteType value ',' value		#udivInst
	|'sdiv' concreteType value ',' value		#sdivInst
	|'fdiv' concreteType value ',' value		#fdivInst
	|'urem' concreteType value ',' value		#uremInst
	|'srem' concreteType value ',' value		#sremInst
	|'frem' concreteType value ',' value		#fremInst
;

valueInstruction:
	//算数指令
	mathInstruction #mathInstruction_
	// Memory instructions
	| allocaInst	#allocaInst_
	| loadInst		#loadInst_
	| getElementPtrInst #GEPInst_
	// Conversion instructions
	| zExtInst 		#zExtInst_
	| sExtInst		#sExtInst_
	| siToFpInst	#siToFpInst_
	| fpToSiInst	#fpToSiInst_
	| bitCastInst	#bitCastInst_
	// Other instructions
	| iCmpInst		#iCmpInst_
	| fCmpInst		#fCmpInst_
	| callInst		#callInst_
;

//store instructions
storeInst:
	'store'concreteType value ',' concreteType value;


//memory instructions
allocaInst:
	'alloca' type (
		',' concreteType value
	)?;
loadInst:
	'load' type ',' concreteType value;
getElementPtrInst:
	'getelementptr'  type ',' concreteType value (',' concreteType value)*;

//conversion instructions
bitCastInst:
	'bitcast' concreteType value 'to' type;
zExtInst:
	'zext' concreteType value 'to' type;
sExtInst: 
	'sext' concreteType value 'to' type;
siToFpInst:
	'sitofp' concreteType value 'to' type;
fpToSiInst:
	'fptosi' concreteType value 'to' type;

//other instructions
iCmpInst:
	'icmp' iPred concreteType value ',' value;
fCmpInst:
	'fcmp' fPred concreteType value ',' value;
callInst:
	'call' type value '(' args ')';

//terminator instructions
retTerm:
	'ret' 'void'
	|'ret' concreteType value;
brTerm: 'br' label;
condBrTerm:
	'br' IntType value ',' label ',' label;

//need fragment
fragment AsciiLetter: [A-Za-z];
fragment Letter: AsciiLetter | [-$._];
fragment EscapeLetter: Letter | '\\';
fragment DecimalDigit: [0-9];
fragment HexDigit: [A-Fa-f] | DecimalDigit;
fragment Decimals: DecimalDigit+;
fragment Name: Letter (Letter | DecimalDigit)*;
fragment EscapeName:
	EscapeLetter (EscapeLetter | DecimalDigit)*;
fragment Id: Decimals;
fragment IntHexLit: [us] '0x' HexDigit+;
// 浮点型常量
fragment Sign: [+-];
fragment FracLit: Sign? Decimals '.' DecimalDigit*;
fragment SciLit: FracLit [eE] Sign? Decimals;

fragment FloatHexLit: '0x' [KLMHR]? HexDigit+;
fragment GlobalName: '@' (Name | QuotedString);
fragment GlobalId: '@' Id;
fragment LocalName: '%' (Name | QuotedString);
fragment LocalId: '%' Id;
fragment QuotedString: '"' (~["\r\n])* '"';

Comment: ';' .*? '\r'? '\n' -> channel(HIDDEN);//注释
WhiteSpace: [ \t\n\r]+ -> skip;
IntLit: '-'? DecimalDigit+ | IntHexLit;
FloatLit: FracLit | SciLit | FloatHexLit;
StringLit: QuotedString;
GlobalIdent: GlobalName | GlobalId;
LocalIdent: LocalName | LocalId;
LabelIdent: (Letter | DecimalDigit)+ ':' | QuotedString ':';
IntType: 'i' DecimalDigit+;

floatType:
	'float'
	;

concreteType:
	intType
	| floatType
	| pointerType
	| labelType
	| arrayType
	| namedType;
value:
	constant
	// %42 %foo
	| LocalIdent
	| GlobalIdent;
constant:
	boolConst
	| intConst
	| floatConst
	| arrayConst
	| zeroInitializerConst;

boolConst: 'true' | 'false';
intConst: IntLit;
floatConst: FloatLit;

arrayConst:
	'[' (concreteType constant (',' concreteType constant)*)? ']';


type:
	'void'
	| type '(' params ')'
	| intType
	| 'float'
	| labelType
	| arrayType
	| type '*'
	| namedType;
	
intType:
	IntType;
pointerType:
	type  '*' ;
labelType:
	'label';
arrayType:
	'[' IntLit 'x' type ']';
namedType:
	LocalIdent;

params: (param (',' param)*)?;
param: type LocalIdent?;
label: 'label' LocalIdent;
iPred:
	'eq'
	| 'ne'
	| 'sge'
	| 'sgt'
	| 'sle'
	| 'slt'
	| 'uge'
	| 'ugt'
	| 'ule'
	| 'ult';

args:
	(arg (',' arg)*)?;
arg: concreteType value;
zeroInitializerConst: 'zeroinitializer';

fPred:
	'false'
	| 'oeq'
	| 'oge'
	| 'ogt'
	| 'ole'
	| 'olt'
	| 'one'
	| 'ord'
	| 'true'
	| 'ueq'
	| 'uge'
	| 'ugt'
	| 'ule'
	| 'ult'
	| 'une'
	| 'uno';


