import { UserRoleId } from '@/constants'

const dashboardItems = [
  {
    name: 'Управелние персоналом',
    href: '/dashboard/employees',
    component: 'EmployeesView',
    meta: {
      title: 'Управелние персоналом',
    },
    roles: [UserRoleId.ADMIN],
  },
]

export default dashboardItems
