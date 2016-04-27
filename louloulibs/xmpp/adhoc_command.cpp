#include <xmpp/adhoc_command.hpp>
#include <xmpp/xmpp_component.hpp>
#include <utils/reload.hpp>

using namespace std::string_literals;

AdhocCommand::AdhocCommand(std::vector<AdhocStep>&& callbacks, const std::string& name, const bool admin_only):
  name(name),
  callbacks(std::move(callbacks)),
  admin_only(admin_only)
{
}

bool AdhocCommand::is_admin_only() const
{
  return this->admin_only;
}

void PingStep1(XmppComponent&, AdhocSession&, XmlNode& command_node)
{
  XmlNode note("note");
  note["type"] = "info";
  note.set_inner("Pong");
  command_node.add_child(std::move(note));
}

void HelloStep1(XmppComponent&, AdhocSession&, XmlNode& command_node)
{
  XmlNode x("jabber:x:data:x");
  x["type"] = "form";
  XmlNode title("title");
  title.set_inner("Configure your name.");
  x.add_child(std::move(title));
  XmlNode instructions("instructions");
  instructions.set_inner("Please provide your name.");
  x.add_child(std::move(instructions));
  XmlNode name_field("field");
  name_field["var"] = "name";
  name_field["type"] = "text-single";
  name_field["label"] = "Your name";
  XmlNode required("required");
  name_field.add_child(std::move(required));
  x.add_child(std::move(name_field));
  command_node.add_child(std::move(x));
}

void HelloStep2(XmppComponent&, AdhocSession& session, XmlNode& command_node)
{
  // Find out if the name was provided in the form.
  if (const XmlNode* x = command_node.get_child("x", "jabber:x:data"))
    {
      const XmlNode* name_field = nullptr;
      for (const XmlNode* field: x->get_children("field", "jabber:x:data"))
        if (field->get_tag("var") == "name")
          {
            name_field = field;
            break;
          }
      if (name_field)
        {
          if (const XmlNode* value = name_field->get_child("value", "jabber:x:data"))
            {
              XmlNode note("note");
              note["type"] = "info";
              note.set_inner("Hello "s + value->get_inner() + "!"s);
              command_node.delete_all_children();
              command_node.add_child(std::move(note));
              return;
            }
        }
    }
  command_node.delete_all_children();
  XmlNode error(ADHOC_NS":error");
  error["type"] = "modify";
  XmlNode condition(STANZA_NS":bad-request");
  error.add_child(std::move(condition));
  command_node.add_child(std::move(error));
  session.terminate();
}

void Reload(XmppComponent&, AdhocSession&, XmlNode& command_node)
{
  ::reload_process();
  command_node.delete_all_children();
  XmlNode note("note");
  note["type"] = "info";
  note.set_inner("Configuration reloaded.");
  command_node.add_child(std::move(note));
}
