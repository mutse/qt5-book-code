VERSION 5.00
Begin VB.Form EditDialog 
   BorderStyle     =   3  'Fixed Dialog
   Caption         =   "Dialog Caption"
   ClientHeight    =   2040
   ClientLeft      =   4275
   ClientTop       =   3690
   ClientWidth     =   6030
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2040
   ScaleWidth      =   6030
   ShowInTaskbar   =   0   'False
   Begin VB.TextBox PhoneEdit 
      Height          =   285
      Left            =   1320
      TabIndex        =   2
      Top             =   1560
      Width           =   3135
   End
   Begin VB.TextBox AddressEdit 
      Height          =   765
      Left            =   1320
      MultiLine       =   -1  'True
      TabIndex        =   1
      Top             =   720
      Width           =   3135
   End
   Begin VB.TextBox NameEdit 
      Height          =   285
      Left            =   1320
      TabIndex        =   0
      Top             =   240
      Width           =   3135
   End
   Begin VB.CommandButton CancelButton 
      Caption         =   "Cancel"
      Height          =   375
      Left            =   4680
      TabIndex        =   4
      Top             =   600
      Width           =   1215
   End
   Begin VB.CommandButton OKButton 
      Caption         =   "OK"
      Height          =   375
      Left            =   4680
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Phone:"
      Height          =   255
      Left            =   240
      TabIndex        =   7
      Top             =   1560
      Width           =   855
   End
   Begin VB.Label AddressLabel 
      Caption         =   "&Address:"
      Height          =   255
      Left            =   240
      TabIndex        =   6
      Top             =   720
      Width           =   975
   End
   Begin VB.Label NameLbl 
      Caption         =   "&Name:"
      Height          =   255
      Left            =   240
      TabIndex        =   5
      Top             =   240
      Width           =   495
   End
End
Attribute VB_Name = "EditDialog"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Public Ok As Boolean
Public Entry As ABItem

Option Explicit

Private Sub Form_Activate()
    Ok = False
    NameEdit.SetFocus
End Sub

Private Sub CancelButton_Click()
    Hide
End Sub

Private Sub OKButton_Click()
    Ok = True
    Hide
End Sub
