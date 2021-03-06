# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";

+EXP lvalue WidgetClass xmDrawingAreaWidgetClass;

+TYPE (struct) _XmDrawingAreaClassRec;
+TYPE (struct) _XmDrawingAreaRec;
+TYPEDEF _XmDrawingAreaClassRec * XmDrawingAreaWidgetClass;
+TYPEDEF _XmDrawingAreaRec * XmDrawingAreaWidget;

+FUNC Widget XmCreateDrawingArea( Widget parent, String name, ArgList arglist,
				 Cardinal argcount) ;

