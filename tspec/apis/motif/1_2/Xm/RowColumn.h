/*
    COPYRIGHT NOTICE

    This program is the proprietary property of the Secretary of State
    for Defence (United Kingdom) acting through the Defence Research
    Agency (DRA).  Use, reproduction, production of amended versions
    and/or transfer of this program is permitted PROVIDED THAT:

    (a)	 This legend be preserved on any such reproduction and amended
	 version.

    (b)	 Any amended version of this program be clearly marked to show
	 the nature of the amendment and the name of the amending
	 organisation.

    (c)	 Any recipient of such reproduction or amended version accept
	 the conditions set out in this legend.

    The DRA accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Crown Copyright (c) 1994.
*/

/*
    COPYRIGHT NOTICE

    This program contains amendments to Motif 1.1 API headers in
    order to represent the Motif 1.2 API. These amendments are the
    property of IXI Ltd, a subsidiary of the Santa Cruz Operation (SCO).
    Use, reproduction, production of amended versions and/or transfer of
    this program is permitted PROVIDED THAT:

    (a)  This legend be preserved on any such reproduction and amended
         version.

    (b)  Any recipient of such reproduction or amended version accept
         the conditions set out in this legend.

    IXI accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Copyright (c) 1995, 1996
*/


/* SCO CID (IXI) RowColumn.h,v 1.1 1996/08/08 14:13:18 wendland Exp */

+USE "motif/1_2","Xm/Xm.h";

+EXP lvalue WidgetClass xmRowColumnWidgetClass;

+TYPE (struct) _XmRowColumnClassRec;
+TYPE (struct) _XmRowColumnWidgetRec;
+TYPEDEF _XmRowColumnClassRec * XmRowColumnWidgetClass;
+TYPEDEF _XmRowColumnWidgetRec * XmRowColumnWidget;


+FUNC Widget XmCreateRadioBox (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateRowColumn (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateWorkArea (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreatePopupMenu (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreatePulldownMenu (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC Widget XmCreateOptionMenu (Widget parent, String name, ArgList arglist,Cardinal argcount);
+FUNC Widget XmCreateMenuBar (Widget parent, String name, ArgList arglist, Cardinal argcount);
+FUNC void XmMenuPosition (Widget parent, XButtonPressedEvent *event);
+FUNC Widget XmOptionLabelGadget (Widget m);
+FUNC Widget XmOptionButtonGadget (Widget m);
+FUNC Widget XmGetPostedFromWidget (Widget menu);
+FUNC Widget XmGetTearOffControl(Widget menu);
+FUNC void XmAddToPostFromList(Widget, Widget);
+FUNC void XmRemoveFromPostFromList(Widget, Widget);
