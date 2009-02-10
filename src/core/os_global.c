/* OperServ core functions
 *
 * (C) 2003-2009 Anope Team
 * Contact us at team@anope.org
 *
 * Please read COPYING and README for further details.
 *
 * Based on the original code of Epona by Lara.
 * Based on the original code of Services by Andy Church.
 *
 * $Id$
 *
 */
/*************************************************************************/

#include "module.h"

void myOperServHelp(User *u);

class CommandOSGlobal : public Command
{
 public:
	CommandOSGlobal() : Command("GLOBAL", 1, 1)
	{
		this->help_param1 = s_GlobalNoticer;
	}

	CommandReturn Execute(User *u, std::vector<std::string> &params)
	{
		const char *msg = params[1].c_str();

		if (WallOSGlobal)
			ircdproto->SendGlobops(s_OperServ, "\2%s\2 just used GLOBAL command.", u->nick);
		oper_global(u->nick, "%s", msg);
		return MOD_CONT;
	}

	bool OnHelp(User *u, const std::string &subcommand)
	{
		if (!is_services_admin(u))
			return false;

		notice_lang(s_OperServ, u, OPER_HELP_GLOBAL);
		return true;
	}

	void OnSyntaxError(User *u)
	{
		syntax_error(s_OperServ, u, "GLOBAL", OPER_GLOBAL_SYNTAX);
	}
};

class OSGlobal : public Module
{
 public:
	OSGlobal(const std::string &modname, const std::string &creator) : Module(modname, creator)
	{
		this->SetAuthor("Anope");
		this->SetVersion("$Id$");
		this->SetType(CORE);

		this->AddCommand(OPERSERV, new CommandOSGlobal(), MOD_UNIQUE);
		this->SetOperHelp(myOperServHelp);
	}
};

/**
 * Add the help response to anopes /os help output.
 * @param u The user who is requesting help
 **/
void myOperServHelp(User *u)
{
	if (is_services_admin(u))
		notice_lang(s_OperServ, u, OPER_HELP_CMD_GLOBAL);
}

MODULE_INIT("os_global", OSGlobal)
