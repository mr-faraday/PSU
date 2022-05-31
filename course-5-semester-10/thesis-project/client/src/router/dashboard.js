const dashboardItems = [
  {
    name: 'Управелние персоналом',
    href: '/dashboard/employees',
    component: 'EmployeesView',
    meta: {
      title: 'Управелние персоналом',
    }
  },
  {
    name: 'Documents Count By Subject',
    href: '/dashboard/documents-count-by-subject',
    component: 'DocumentsCountBySubjectView',
    meta: {
      title: 'Documents Count By Subject',
    }
  },
  {
    name: 'Document Subject By Name',
    href: '/dashboard/document-subject-by-name',
    component: 'DocumentSubjectByNameView',
    meta: {
      title: 'Document Subject By Name',
    }
  },
  {
    name: 'Document With Largest Copies Number',
    href: '/dashboard/document-with-largest-copies-number',
    component: 'DocumentWithLargestCopiesNumberView',
    meta: {
      title: 'Document With Largest Copies Number',
    }
  },
  {
    name: 'Empty Cells',
    href: '/dashboard/empty-cells',
    component: 'EmptyCellsView',
    meta: {
      title: 'Empty Cells',
    }
  },
  {
    name: 'Empty Space',
    href: '/dashboard/empty-space',
    component: 'EmptySpaceView',
    meta: {
      title: 'Empty Space',
    }
  },
  {
    name: 'Last Subscriber',
    href: '/dashboard/last-subscriber',
    component: 'LastSubscriberView',
    meta: {
      title: 'Last Subscriber',
    }
  },
  {
    name: 'Most Claimed Document',
    href: '/dashboard/most-claimed-document',
    component: 'MostClaimedDocumentView',
    meta: {
      title: 'Most Claimed Document',
    }
  },
  {
    name: 'Unclaimed Documents',
    href: '/dashboard/unclaimed-documents',
    component: 'UnclaimedDocumentsView',
    meta: {
      title: 'Unclaimed Documents',
    }
  },
]

export default dashboardItems
