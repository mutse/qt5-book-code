VERSION 5.00
Begin VB.Form AddressView 
   Caption         =   "Address Book"
   ClientHeight    =   5235
   ClientLeft      =   3105
   ClientTop       =   2190
   ClientWidth     =   8115
   LinkTopic       =   "Form1"
   ScaleHeight     =   5235
   ScaleWidth      =   8115
   Begin VB.CommandButton DeleteEntry 
      Caption         =   "&Delete Entry"
      Height          =   375
      Left            =   6360
      TabIndex        =   3
      Top             =   4800
      Width           =   1575
   End
   Begin VB.CommandButton AddEntry 
      Caption         =   "&Add Entry"
      Height          =   375
      Left            =   3000
      TabIndex        =   1
      Top             =   4800
      Width           =   1575
   End
   Begin VB.CommandButton EditEntry 
      Caption         =   "&Edit Entry"
      Height          =   375
      Left            =   4680
      TabIndex        =   2
      Top             =   4800
      Width           =   1575
   End
   Begin VB.ListBox AddressList 
      Height          =   4545
      Left            =   120
      TabIndex        =   0
      Top             =   120
      Width           =   7815
   End
End
Attribute VB_Name = "AddressView"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim book As AddressBook

Private Sub AddEntry_Click()
    Dim Dialog As EditDialog
    Set Dialog = EditDialog
    Dialog.NameEdit.Text = ""
    Dialog.AddressEdit.Text = ""
    Dialog.PhoneEdit.Text = ""
    Dialog.Show vbModal, Me
    
    If Dialog.Ok = True Then
        Dim Entry As ABItem
        Set Entry = book.createEntry(Dialog.NameEdit.Text)
        Entry.address = Dialog.AddressEdit.Text
        Entry.phoneNumber = Dialog.PhoneEdit.Text
        Update
    End If
End Sub


Private Sub DeleteEntry_Click()
    If AddressList.ListIndex = -1 Then GoTo NoItem
    Dim Entry As ABItem
    Set Entry = book.findEntry(AddressList.List(AddressList.ListIndex))
    Entry.Remove
    Update
NoItem:
End Sub

Private Sub EditEntry_Click()
    If AddressList.ListIndex = -1 Then GoTo NoItem
    
    Dim Dialog As EditDialog
    Set Dialog = EditDialog
   
    Dim Entry As ABItem
    Set Entry = book.findEntry(AddressList.List(AddressList.ListIndex))
    Dialog.NameEdit = Entry.contact
    Dialog.AddressEdit = Entry.address
    Dialog.PhoneEdit = Entry.phoneNumber
    
    Dialog.Show vbModal, Me
    If Dialog.Ok = True Then
        Entry.contact = Dialog.NameEdit.Text
        Entry.address = Dialog.AddressEdit.Text
        Entry.phoneNumber = Dialog.PhoneEdit.Text
    End If
    Update
NoItem:
End Sub

Private Sub Update()
    AddressList.Clear
    For x = 0 To book.Count - 1
        Dim Entry As ABItem
        Set Entry = book.entryAt(x)
        AddressList.AddItem Entry.contact, AddressList.ListCount
    Next
End Sub

Private Sub Form_Load()
    Set book = New AddressBook
    Update
End Sub
